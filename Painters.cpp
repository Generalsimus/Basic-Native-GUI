


//auto BoxPx(float width, float height) {
//    return [width, height](ElementView *element) {
//        std::function < void() > *removeEvent = new std::function<void()>;
//        *removeEvent = []() {
//
//        };
//        element->addDrawEvent([width, height](ElementView *element, SkCanvas *canvas, SkPaint *paint) {
//
//            paint->setColor(SK_ColorRED);
//            paint->setStyle(SkPaint::kStrokeAndFill_Style);
//            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, width, height), *paint);
//
//        }, *removeEvent);
//        element->addSetPaintsEvent([removeEvent](ElementView *element) {
//            (*removeEvent)();
//            delete removeEvent;
//        }, *removeEvent);
//    };
//};
//
//
//auto FullBox() {
//    return [](ElementView *element) {
//        auto *removeEvent = new std::function<void()>;
//        *removeEvent = []() {
//
//        };
//        SkColor *bgColor = new SkColor;
//        *bgColor = SK_ColorWHITE;
//        element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
//            *bgColor = color;
//        }, *removeEvent);
//        element->addDrawEvent([bgColor](ElementView *element, SkCanvas *canvas, SkPaint *paint) {
//
//            paint->setColor(*bgColor);
//
////            paint->setStyle(SkPaint::kFill_Style);
//            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, element->parent->width, element->parent->height),
//                             *paint);
//        }, *removeEvent);
//        element->addSetPaintsEvent([removeEvent, bgColor](ElementView *element) {
//            (*removeEvent)();
//            delete removeEvent;
//            delete bgColor;
//        }, *removeEvent);
//    };
//};
//
//auto BoxPercent(float percentWidth, float percentHeight) {
//    return [percentWidth, percentHeight](ElementView *element) {
//
//        std::function < void() > *removeEvent = new std::function<void()>;
//        *removeEvent = []() {
//
//        };
//        SkColor *bgColor = new SkColor;
//        *bgColor = SK_ColorWHITE;
//        element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
//            *bgColor = color;
//        }, *removeEvent);
//
//
//        if (element->parent == nullptr) {
//            element->addMountOnThreeEvent([&percentHeight, &percentWidth](ElementView *element, ElementView *parent) {
//                element->width = ((percentWidth / 100.0f) * parent->width);
//                element->height = ((percentHeight / 100.0f) * parent->height);
//            }, *removeEvent);
//        } else {
//            element->addResizeEvent([&percentHeight, &percentWidth](ElementView *element, float w, float h) {
//                element->width = ((percentWidth / 100.0f) * element->parent->width);
//                element->height = ((percentHeight / 100.0f) * element->parent->height);
//            }, *removeEvent);
//        }
//        element->addDrawEvent(
//                [percentWidth, percentHeight, bgColor, sizingFunc](ElementView *element, SkCanvas *canvas,
//                                                                   SkPaint *paint) {
//                    printf("RUNNNNNNNNNDRAWWWWWWWWWWW");
////                    sizingFunc();
//                    paint->setColor(*bgColor);
//
//                    paint->setStyle(SkPaint::kStrokeAndFill_Style);
//                    canvas->drawRect(
//                            SkRect::MakeXYWH(element->x, element->y, element->width, element->height), *paint);
//
//                });
//        element->addSetPaintsEvent([removeEvent, bgColor](ElementView *element) {
//            (*removeEvent)();
//            delete removeEvent;
//            delete bgColor;
//        }, *removeEvent);
//    };
//};
//
//auto DirectionRow() {
//    return [](ElementView *element) {
//        std::function < void() > *removeEvent = new std::function<void()>;
//        *removeEvent = []() {
//
//        };
//
//        std::function < void(ElementView * element) > makeAlignmend = [](ElementView *element) {
////            float startAt = element->x;
//
////            for (ElementView *child: element->children) {
////                child->x = startAt;
////                child->y = element->y;
////                startAt = startAt + element->width;
////            }
//        };
//        element->addAddChildEvent([makeAlignmend](ElementView *element, ElementView *newChild) {
//            makeAlignmend(element);
//        }, *removeEvent);
//        element->addResizeEvent([makeAlignmend](ElementView *element, float width, float height) {
//            makeAlignmend(element);
//        }, *removeEvent);
//        element->addSetPaintsEvent([removeEvent](ElementView *element) {
//            (*removeEvent)();
//            delete removeEvent;
//        }, *removeEvent);
//    };
//};
class CreateAPinterOptions {
private:
    using EjectFunction = std::function<void()>;
    ElementView *element;
public:
    CreateAPinterOptions(ElementView *element) : element(element) {
    };

    EjectFunction ejectFunction = []() {};

    template<typename RemoveEventCallBack = std::function<void()>>
    void addEjectCallBack(EjectFunction &&ejectCallBack, RemoveEventCallBack &&removeEventCallBack = nullptr) {
        this->element->addChainFunction(this->ejectFunction, ejectCallBack, removeEventCallBack,
                                        this->ejectFunction == nullptr, false);
    }

    void eject() {
        if (this->ejectFunction != nullptr) {
            this->ejectFunction();
        };
    }
};

template<typename CalBackPaint>
auto CreatePainterWithOption(CalBackPaint &&callBack) {
    return [callBack](ElementView *element) mutable {
        std::function < void() > *ejectFunction = new std::function<void()>;
        if (element->parent == nullptr) {
            element->addMountOnThreeEvent([ejectFunction, callBack](ElementView *element, ElementView *parent) mutable {
                callBack(element, parent, element->window->surface->getCanvas(), &element->window->paint,
                         *ejectFunction);
            }, *ejectFunction);
        } else {
            callBack(element, element->parent, element->window->surface->getCanvas(), &element->window->paint,
                     *ejectFunction);
        }
        element->addSetPaintsEvent([ejectFunction](ElementView *element) {
            (*ejectFunction)();
            delete ejectFunction;
        }, *ejectFunction);
    };
}

auto DirectionRow() {
    return CreatePainterWithOption([](
            ElementView *element,
            ElementView *parentElement,
            auto canvas,
            auto paint,
            auto ejectCallBack
    ) {
        auto resizeCallBack = [element](float width, float height) mutable {
            int childCount = element->children.size();
            float itemWidth = width / static_cast<float>(childCount);

            for (int childIndex = 0; childIndex < childCount; childIndex++) {
                auto child = element->children[childIndex];
                child->x = element->x + childIndex * itemWidth;
                child->y = element->y;
                child->dispatchResizeEvent(itemWidth, height);
            };
        };

        element->addResizeEvent([resizeCallBack](ElementView *element, float newWidth, float newHeight) mutable {
            resizeCallBack(newWidth, newHeight);
        }, ejectCallBack);

        element->addAddChildEvent([resizeCallBack](ElementView *element, ElementView *newChild) mutable {
            resizeCallBack(element->width, element->height);
        }, ejectCallBack);


        resizeCallBack(element->width, element->height);

    });

}


auto Cursor(Cursor cursor) {
    return CreatePainterWithOption([cursor](
            ElementView *element,
            ElementView *parentElement,
            auto canvas,
            auto paint,
            auto ejectCallBack
    ) {
        element->addTouchOverEvent([cursor, ejectCallBack](ElementView *element) mutable {
            auto undoCursor = element->window->setCursor(cursor);
            printf("MOUSE OVER\n");
            element->addTouchLeaveEvent([cursor, undoCursor](ElementView *element) mutable {
                undoCursor();
            }, undoCursor);

        }, ejectCallBack);
    });
}

auto BoxPercent(float percentWidth, float percentHeight) {
    return CreatePainterWithOption([percentWidth, percentHeight](
            ElementView *element,
            ElementView *parentElement,
            auto canvas,
            auto paint,
            auto ejectCallBack
    ) {
        std::function<bool(float, float)> containerFn = [](float x,float y){
//            printf("CONTAIN222 \n");
            return false;
        };
        SkColor *bgColor = new SkColor;
        *bgColor = SK_ColorWHITE;
        auto paintFunc = [element, percentWidth, percentHeight, bgColor, containerFn](SkCanvas *canvas, SkPaint *paint) mutable {
            paint->setColor(*bgColor);
            paint->setStyle(SkPaint::kStrokeAndFill_Style);
            auto rect = SkRect::MakeXYWH(element->x, element->y, (element->width * (percentWidth / 100)),
                                         (element->height * (percentHeight / 100)));
            containerFn = [rect](float x,float y){
                printf("CONTAIN\n");
                return rect.contains(x, y);
            };
            canvas->drawRect(rect, *paint);

        };
        element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
            *bgColor = color;
            element->dispatchDrawEvent();
        }, ejectCallBack);

        element->addDrawEvent([paintFunc](ElementView *element, SkCanvas *canvas, SkPaint *paint) mutable {
            paintFunc(canvas, paint);
        }, ejectCallBack);
//        contains()
        parentElement->addTouchMoveEvent([element, containerFn](ElementView *el, float windowX, float windowY) mutable {
            printf("CONTAIN333 \n");
            if (containerFn(windowX, windowY)) {
//                    (windowX > element->x) &&
//                    (windowX < (element->x + element->width)) &&
//                    (windowY > element->y) &&
//                    (windowY < (element->y + element->height))


                element->dispatchTouchOverEvent();
            }
        }, ejectCallBack);
//        element->addSetPaintsEvent([bgColor](ElementView *element) {
////            delete bgColor;
//        }, ejectCallBack);

        paintFunc(canvas, paint);
    });

}