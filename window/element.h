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
#include "./asyncTaskController.h"


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

    /// START ADD PAINT FIGuRES //
    template<typename PaintFunction, typename... Args>
    Element *setPaints(PaintFunction paintCallback, Args... args) {
        dispatchSetPaintsEvent();

        SetEachPainters(paintCallback, std::forward<Args>(args)...);

        return this;
    };
    /// End ADD PAINT FIGuRES //

    /// EVENTS LIST //////////////////////////////////////////////////
    /// TOUCH MOVIE

    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addTouchMoveEvent(TouchMoveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchTouchMoveEvent(int windowX, int windowY, bool isAsync = true, bool useTouchOverChild = true);

    /// TOUCH OVER
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addTouchOverEvent(TouchOverEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchTouchOverEvent();

    /// TOUCH LEAVE
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addTouchLeaveEvent(TouchLeaveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchTouchLeaveEvent();

    /// TOUCH DOWN

    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addTouchDownEvent(TouchDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchTouchDownEvent(int windowX, int windowY, int typeIndex);

    /// TOUCH UP
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addTouchUpEvent(TouchUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchTouchUpEvent(int windowX, int windowY, int typeIndex);

    /// TOUCH
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addTouchEvent(TouchEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchTouchEvent(int windowX, int windowY, int typeIndex);

    /// KEY DOWN
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addKeyDownEvent(KeyDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchKeyDownEvent(int keyIndex);

    /// KEY Up
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addKeyUpEvent(KeyUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchKeyUpEvent(int keyIndex);

    /// KEY
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addKeyEvent(KeyEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchKeyEvent(int keyIndex);

    /// Draw
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addDrawEvent(DrawEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchDrawEvent(SkCanvas *canvas, SkPaint *paint);

    /// Set Paints
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addSetPaintsEvent(SetPaintsEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchSetPaintsEvent();

    /// RESIZE ELEMENT
    template<typename RemoveEventCallBack = std::function<void()>>
    Element *addResizeEvent(ResizeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Element *dispatchResizeEvent(float windowWidth, float windowHeight);

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

    DrawEventType DrawEventChain = nullptr;

    SetPaintsEventType SetPaintsEventChain = nullptr;

    ResizeEventType ResizeEventChain = nullptr;

    /// EVENTS CHAIN END



    /// START EVENT VARIABLES
    bool isMouseOver = false;
    /// END EVENT VARIABLES

    /// START DRAWER PRIVATE OPTIONS  //


    void SetEachPainters();
    template<typename PaintFunction, typename... Args>
    void SetEachPainters(PaintFunction paintCallback, Args... args);
    /// END DRAWER PRIVATE OPTIONS  //

protected:


    template<typename CallBackFunction, typename RemoveEventCallBack>
    void addChainFunction(CallBackFunction &chainFunc, CallBackFunction &callBack,
                          RemoveEventCallBack &removeChainFunction = nullptr,
                          bool startFromNewPoint = false,
                          bool callAsync = true);

//    template<typename ChainFunc, typename... Args>
    template<class ChainFunc, class... Args>
    void dispatchChainFunction(ChainFunc &chainFunc, Args &&... args);

    void InitCustomEventListeners();


    void drawMe() {
        return;
    };
};


#endif //CUDA_NEU_ELEMENT_H
