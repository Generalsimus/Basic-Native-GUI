


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
template<typename CalBackPaint>
auto CreatePainterWithOption(CalBackPaint &&callBack) {
    return [callBack](ElementView *element) mutable {
//      return ;
        std::shared_ptr<std::function<void()>> ejectFunction = std::make_shared<std::function<void()>>([]() {});
//        std::function<void()> *ejectFunction = new std::function<void()>([](){});
//
//        *ejectFunction = [](){};
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
//            delete ejectFunction;
        }, *ejectFunction);
    };
}

auto DirectionRow() {
    return CreatePainterWithOption(
            [](ElementView *element, ElementView *parentElement, auto canvas, auto paint, auto ejectCallBack) {

                auto resizeCallBack = [element](float width, float height) mutable {
                    int childCount = element->children.size();
                    float itemWidth = width / static_cast<float>(childCount);
//                    std::cout << "childCount: " << childCount <<" "<< itemWidth << std::endl;
                    for (int childIndex = 0; childIndex < childCount; childIndex++) {
                        auto child = element->children[childIndex];
                        child->x = element->x + childIndex * itemWidth;
                        child->y = element->y;


//                        std::cout << "X: " << child->x << " Y: " << child->y << std::endl;
//                        std::cout << "itemWidth: " << itemWidth << " height: " << height << std::endl;
                        child->dispatchResizeEvent(itemWidth, height);
                    };
                };

                element->addResizeEvent(
                        [resizeCallBack](ElementView *element, float newWidth, float newHeight) mutable {
                            resizeCallBack(newWidth, newHeight);
                        }, ejectCallBack);

                element->addAddChildEvent([resizeCallBack](ElementView *element, ElementView *newChild) mutable {
                    resizeCallBack(element->width, element->height);
                    element->draw();
                }, ejectCallBack);

                resizeCallBack(element->width, element->height);

            });

}


auto Cursor(Cursor cursor) {
    return CreatePainterWithOption(
            [cursor](ElementView *element, ElementView *parentElement, auto canvas, auto paint, auto ejectCallBack) {
//                element->addTouchOverEvent([cursor, ejectCallBack](ElementView *element) mutable {
//                    auto undoCursor = element->window->setCursor(cursor);
//                    printf("MOUSE OVER\n");
////            element->dispatchSetBackgroundColorEvent(SK_ColorRED);
////            element->parent->dispatchDrawEvent();
//
//                    element->addTouchLeaveEvent([cursor, undoCursor](ElementView *element) mutable {
////                element->dispatchSetBackgroundColorEvent(SkColorSetARGB(255, 0, 128, 0));
////                element->parent->dispatchDrawEvent();
//
//                        undoCursor();
//                    }, undoCursor);
//
//                }, ejectCallBack);
            });
}

//std::mutex mutex2_;
//std::mutex skiaMutex;

auto BoxPercent(float percentWidth, float percentHeight) {
    return CreatePainterWithOption(
            [percentWidth, percentHeight](ElementView *element, ElementView *parentElement, auto canvas, auto paint,
                                          auto ejectCallBack) {


                std::shared_ptr<SkRect> sharedRect = std::make_shared<SkRect>(
                        SkRect::MakeXYWH(element->x, element->y, (element->width * (percentWidth / 100)),
                                         (element->height * (percentHeight / 100))));

                element->addResizeEvent([percentWidth, percentHeight, sharedRect](ElementView *element, float newWidth,
                                                                                  float newHeight) {
                    sharedRect->setXYWH(element->x, element->y, (element->width * (percentWidth / 100)),
                                        (element->height * (percentHeight / 100)));

                }, ejectCallBack);

                std::shared_ptr<SkColor> bgColor = std::make_shared<SkColor>(SK_ColorWHITE);

                element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
                    *bgColor = color;
                }, ejectCallBack);

                element->addDrawEvent(
                        [bgColor, sharedRect, percentWidth, percentHeight](ElementView *element, SkCanvas *canvas,
                                                                           SkPaint *paint) {
//                            skiaMutex.lock();
//                            std::unique_lock lock1(skiaMutex);

                            paint->setColor(*bgColor);

                            canvas->drawRect(*sharedRect, *paint);

//                            lock1.unlock();

//                    std::cout << "RUN DRAW AT: " << std::endl;
                        }, ejectCallBack);
//                parentElement->addTouchMoveEvent([]() {
//
//                });


                element->addContainsFn([sharedRect](float x, float y) mutable {
                    return sharedRect->contains(x, y);
                });
//                contains
//
//
//                std::shared_ptr<SkColor> bgColor = std::make_shared<SkColor>(SK_ColorWHITE);
//
//                auto paintFunc = [element, percentWidth, percentHeight, bgColor, sharedRect](SkCanvas *canvas,
//                                                                                             SkPaint *paint) {
//                    paint->setColor(*bgColor);
////
////            sharedRect->setXYWH(element->x, element->y, (element->width * (percentWidth / 100)),
////                         (element->height * (percentHeight / 100)));
//
//                    canvas->drawRect(*sharedRect, *paint);
//
//                };
//                element->addResizeEvent([percentWidth, percentHeight, sharedRect](ElementView *element, float newWidth,
//                                                                                  float newHeight) {
//
//                    sharedRect->setXYWH(element->x, element->y, (element->width * (percentWidth / 100)),
//                                        (element->height * (percentHeight / 100)));
//                }, ejectCallBack);
//
//                element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
//                    *bgColor = color;
//
//                    element->dispatchDrawEvent();
//                }, ejectCallBack);
//
//                element->addDrawEvent([paintFunc](ElementView *element, SkCanvas *canvas, SkPaint *paint) {
//                    paintFunc(canvas, paint);
//                }, ejectCallBack);
//
//                paintFunc(canvas, paint);
//
//                element->addContainsFn([sharedRect](float x, float y) mutable {
//                    return sharedRect->contains(x, y);
//                });

            });

}