//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_ELEMENT_H
#define CUDA_NEU_ELEMENT_H

#include "functional"
#include "Windows.h"
#include "string"
#include <cstddef>
#include <vector>
#include <future>
#include "include/core/SkPaint.h"
#include "include/core/SkCanvas.h"
#include "./eventsType.h"
#include "asyncTaskController.h"


class Element : public AsyncTaskController {
public:

    float x;
    float y;
    float width;
    float height;


    Element *parent;
    /// START CHILD OPTIONS //
    std::vector<Element *> children;


    Element *addChildElement();

    template<typename... Chi>
    Element *addChildElement(Element *child, Chi... rest);

    /// END CHILD OPTIONS //
    bool PositionIsOver(int x, int y);


    Element();

    template<typename... Args>
    explicit Element(Element *first, Args... rest);

    /// START ASYNC CONTROLLERS //


    void CreateAsyncGroup();
    /// END ASYNC CONTROLLERS //

    /// START ADD PAINT FIGuRES //
//    template<typename Func, typename... Args>
    void addShapes() {

    }
    /// End ADD PAINT FIGuRES //

    /// EVENTS LIST //////////////////////////////////////////////////
    /// TOUCH MOVIE
    Element *addTouchMovieEvent(TouchMoveEventType &&callBack);

    Element *dispatchTouchMovieEvent(int windowX, int windowY, bool isAsync = true, bool useTouchOverChild = true);

    /// TOUCH OVER
    Element *addTouchOverEvent(TouchOverEventType &&callBack);

    Element *dispatchTouchOverEvent();

    /// TOUCH LEAVE
    Element *addTouchLeaveEvent(TouchLeaveEventType &&callBack);

    Element *dispatchTouchLeaveEvent();

    /// TOUCH DOWN
    Element *addTouchDownEvent(TouchDownEventType &&callBack);

    Element *dispatchTouchDownEvent(int windowX, int windowY, int typeIndex);

    /// TOUCH UP
    Element *addTouchUpEvent(TouchUpEventType &&firstCallBack);

    Element *dispatchTouchUpEvent(int windowX, int windowY, int typeIndex);

    /// TOUCH
    Element *addTouchEvent(TouchEventType &&firstCallBack);

    Element *dispatchTouchEvent(int windowX, int windowY, int typeIndex);

    /// KEY DOWN
    Element *addKeyDownEvent(KeyDownEventType &&callBack);

    Element *dispatchKeyDownEvent(int keyIndex);

    /// KEY Up
    Element *addKeyUpEvent(KeyUpEventType &&callBack);

    Element *dispatchKeyUpEvent(int keyIndex);

    /// KEY
    Element *addKeyEvent(KeyUpEventType &&callBack);

    Element *dispatchKeyEvent(int keyIndex);

    /// Draw
    Element *addDrawEvent(DrawEventType &&callBack);

    Element *dispatchDrawEvent(SkCanvas canvas);
    /// Draw
    /// EVENTS LIST END /////////////////////////////////////////////////


private:

    /// CHAIN FOR DEFAULT STYLES
    std::function<void(Element *)> DrawStylesChain = nullptr;

    /// EVENTS CHAIN START
    TouchOverEventType TouchOverEventChain = nullptr;
    TouchLeaveEventType TouchLeaveEventChain = nullptr;

    TouchMoveEventType TouchMoveEventChain = nullptr;
    TouchDownEventType TouchDownEventChain = nullptr;
    TouchUpEventType TouchUpEventChain = nullptr;
    TouchEventType TouchEventChain = nullptr;

    KeyDownEventType KeyDownEventChain = nullptr;
    KeyUpEventType KeyUpEventChain = nullptr;
    KeyEventType KeyEventChain = nullptr;
    /// EVENTS CHAIN END



    /// START EVENT VARIABLES
    bool isMouseOver = false;
    /// END EVENT VARIABLES
    SkPaint paint;


protected:

    template<typename CallBackFunction>
    void addChainFunction(CallBackFunction &chainFunc, CallBackFunction &callBack, bool startFromNewPoint = false,
                          bool callAsync = true);

//    template<typename ChainFunc, typename... Args>
    template<class ChainFunc, class... Args>
    void dispatchChainFunction(ChainFunc &chainFunc, Args &&... args);

    void InitCustomEventListeners();


    void drawMe() {
        return;
    }
};

//addBackGround
//addStyleBackgroundEvent();
//addStyleBackgroundEvent();
auto Box(float widthParcentSize, float parcentSize) {
    return []() {
//        SkRect contentRect = SkRect::MakeLTRB(50.0f, 50.0f, 350.0f, 150.0f);
    };
};

//auto BackgroundColor(SkColor color) {
//    return [](SkCanvas *canvas, SkPaint paint) {
////        paint.setColor(SK_ColorBLACK);
////        SkPaint paint;
//        paint.setColor(SK_ColorRED);
////        canvas->drawRect(SkRect::MakeXYWH(100, 100, 200, 200), paint);
//
//    };
//}
//
//auto BoxPX(int Width, int height) {
//    return [](Element *element, SkCanvas *canvas, const SkPaint &paint) {
////        paint.setColor(SK_ColorBLACK);
////        SkPaint paint;
////        paint.setColor(SK_ColorRED);
////        element->x
////        element->y
////        element->width
////        element->height
//        canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, element->width, element->height), paint);
//
//    }
//}
//
//auto BoxPX(int Width, int height) {
//    return [](Element *parent, Element *element, SkCanvas *canvas, const SkPaint &paint) {
////        paint.setColor(SK_ColorBLACK);
////        SkPaint paint;
////        paint.setColor(SK_ColorRED);
////        element->x
////        element->y
////        element->width
////        element->height
//        canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, element->width, element->height), paint);
//
//    }
//}
#endif //CUDA_NEU_ELEMENT_H
