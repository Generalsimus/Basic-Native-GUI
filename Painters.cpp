//#include ".drawTextBlob"
#include "include/core/SkTextBlob.h"


template<typename CalBackPaint>
auto CreatePainterWithOption(CalBackPaint &&callBack) {
    return [callBack](ElementView *element) mutable {
        std::shared_ptr<std::function<void()>> ejectFunction = std::make_shared<std::function<void()>>([]() {});

        callBack(element, *ejectFunction);


        element->addSetPaintsEvent([ejectFunction](ElementView *element) {
            (*ejectFunction)();
        }, *ejectFunction);
    };
}


auto DirectionRow() {
    return CreatePainterWithOption([](ElementView *element, auto ejectCallBack) {
        auto resizeCallBack = [](ElementView *element, float width, float height) mutable {
            int childCount = element->children.size();
            float itemWidth = width / static_cast<float>(childCount);
//                    std::cout << "childCount: " << childCount <<" "<< itemWidth << std::endl;
            for (int childIndex = 0; childIndex < childCount; childIndex++) {
                auto child = element->children[childIndex];
                child->x = element->x + childIndex * itemWidth;
                child->y = element->y;

                child->width = itemWidth;
                child->height = height;

                child->dispatchResizeEvent(itemWidth, height);
            };
        };

        element->addResizeEvent(
                [resizeCallBack](ElementView *element, float newWidth, float newHeight) mutable {
                    resizeCallBack(element, newWidth, newHeight);
                }, ejectCallBack);
        element->addAddChildEvent([resizeCallBack](ElementView *element, ElementView *newChild) mutable {
            resizeCallBack(element, element->width, element->height);
            element->draw();
        }, ejectCallBack);


        resizeCallBack(element, element->width, element->height);
    });

}


auto Cursor(Cursor cursor) {
    return CreatePainterWithOption(
            [cursor](ElementView *element, auto ejectCallBack) {


                std::shared_ptr<std::function<void()>> currentCursor = std::make_shared<std::function<void()>>(nullptr);

                element->addTouchOverEvent([cursor, currentCursor](ElementView *element) {
                    if (element->window != nullptr) {
                        *currentCursor = element->window->setCursor(cursor);
                    }
                }, ejectCallBack);

                element->addTouchLeaveEvent([cursor, currentCursor](ElementView *element) {
                    if (*currentCursor != nullptr) {
                        (*currentCursor)();
                        *currentCursor = nullptr;
                    }
                }, ejectCallBack);

            });
}

auto BoxPercent(float percentWidth, float percentHeight) {

    return CreatePainterWithOption([percentWidth, percentHeight](ElementView *element, auto ejectCallBack) {
        std::shared_ptr<SkColor> bgColor = std::make_shared<SkColor>(SK_ColorWHITE);
        element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
            *bgColor = color;
        }, ejectCallBack);


        std::shared_ptr<SkRect> sharedRect = std::make_shared<SkRect>(
                SkRect::MakeXYWH(element->x, element->y, (element->width * (percentWidth / 100)),
                                 (element->height * (percentHeight / 100))));
        element->addResizeEvent([percentWidth, percentHeight, sharedRect](ElementView *element, float newWidth,
                                                                          float newHeight) {
            sharedRect->setXYWH(element->x, element->y, (element->width * (percentWidth / 100)),
                                (element->height * (percentHeight / 100)));

        }, ejectCallBack);


        element->addDrawEvent([bgColor, sharedRect, percentWidth, percentHeight](ElementView *element, SkCanvas *canvas,
                                                                                 SkPaint *paint) {
            paint->setColor(*bgColor);

            canvas->drawRect(*sharedRect, *paint);

        }, ejectCallBack);


        element->addContainsFn([sharedRect](float x, float y) mutable {
            return sharedRect->contains(x, y);
        });


    });

}

auto Box() {
    return BoxPercent(100, 100);
}


auto Text(std::string defaultText, bool isEditable = false) {
    return CreatePainterWithOption([defaultText, isEditable](ElementView *element, auto ejectCallBack) {

        element->addDrawEvent([defaultText](ElementView *element, SkCanvas *canvas, SkPaint *paint) {
            auto  fontSize = 45.0f;
            paint->setAntiAlias(true);
            paint->setColor(SkColorSetRGB(255, 0, 0));
            paint->setStyle(SkPaint::kStrokeAndFill_Style);
//            paint->setStrokeWidth(3.0f);
            auto text = SkTextBlob::MakeFromString(defaultText.c_str(), SkFont(nullptr, fontSize));


            canvas->drawTextBlob(text.get(), element->x, element->y + fontSize, *paint);
            paint->setStyle(SkPaint::kFill_Style);
        }, ejectCallBack);


    });

}
