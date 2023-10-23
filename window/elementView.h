//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_ELEMENTVIEW_H
#define CUDA_NEU_ELEMENTVIEW_H

#include "./eventsType.h"
#include "Windows.h"
#include "functional"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "string"
#include <cstddef>
#include <future>
#include <vector>

class Window;

class ElementView {
public:
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    ElementView *parent = nullptr;
    Window *window = nullptr;
    bool isMouseOver = false;
    /// START CHILD OPTIONS //
    std::vector<ElementView *> children;

    ElementView *addChild();

    template<typename... Chi>
    ElementView *addChild(ElementView *child, Chi... rest);

    void replaceChild(int replaceAtIndex, ElementView *newChild);

    void removeChild(int startIndex, int removeCount = 1);

    /// END CHILD OPTIONS //

    //    bool PositionIsOver(int x, int y);

    ElementView();

    template<typename... Args>
    explicit ElementView(ElementView *first, Args... rest);

    /// START ADD PAINT FIGuRES //

    template<typename PaintFunction, typename... Args>
    ElementView *setPaints(PaintFunction paintCallback, Args... args);

    /// End ADD PAINT FIGuRES //

    /// EVENTS LIST //////////////////////////////////////////////////
    /// TOUCH MOVIE

    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchMoveEvent(TouchMoveEventType &&callBack,
                                   RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchTouchMoveEvent(Args &&... args);

//      bool isAsync = true,
//           bool useTouchOverChild = true
    /// TOUCH OVER
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchOverEvent(TouchOverEventType &&callBack,
                                   RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchTouchOverEvent();

    /// TOUCH LEAVE
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchLeaveEvent(TouchLeaveEventType &&callBack,
                                    RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchTouchLeaveEvent();

    /// TOUCH DOWN
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchDownEvent(TouchDownEventType &&callBack,
                                   RemoveEventCallBack &&removeEventCallBack = nullptr);


    template<typename... Args>
    ElementView *dispatchTouchDownEvent(Args &&... args);

    /// TOUCH UP
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchUpEvent(TouchUpEventType &&callBack,
                                 RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchTouchUpEvent(Args &&... args);

    /// TOUCH
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchEvent(TouchEventType &&callBack,
                               RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchTouchEvent(Args &... args);

    /// KEY DOWN
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addKeyDownEvent(KeyDownEventType &&callBack,
                                 RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchKeyDownEvent(Args &&... args);

    /// KEY Up
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addKeyUpEvent(KeyUpEventType &&callBack,
                               RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchKeyUpEvent(Args &&... args);

    /// KEY
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addKeyEvent(KeyEventType &&callBack,
                             RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchKeyEvent(Args &&... args);

    /// Draw
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addDrawEvent(DrawEventType &&callBack,
                              RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchDrawEvent(Args &&... args);

    ElementView *draw();

    /// RESIZE ELEMENT
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addResizeEvent(ResizeEventType &&callBack,
                                RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchResizeEvent(Args &... args);

    /// Set Paints
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addSetPaintsEvent(SetPaintsEventType &&callBack,
                                   RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchSetPaintsEvent();

    /// ADD CHILD
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addAddChildEvent(AddChildEventType &&callBack,
                                  RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchAddChildEvent(Args &... args);

    /// REMOVE CHILD
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addRemoveChildEvent(RemoveChildEventType &&callBack,
                                     RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchRemoveChildEvent(Args &... args);

    /// REPLACE CHILD
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addReplaceChildEvent(ReplaceChildEventType &&callBack,
                                      RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchReplaceChildEvent(Args &... args);

    /// SetBackground
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addSetBackgroundColorEvent(SetBackgroundColorEventType &&callBack,
                                            RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchSetBackgroundColorEvent(Args &&... args);

    /// MountOnThree
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addMountOnThreeEvent(MountOnThreeEventType &&callBack,
                                      RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchMountOnThreeEvent(Args &&... args);

    /// UnmountOnThree
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addUnmountOnThreeEvent(UnmountOnThreeEventType &&callBack,
                                        RemoveEventCallBack &&removeEventCallBack = nullptr);

    template<typename... Args>
    ElementView *dispatchUnmountOnThreeEvent(Args &&... args);

    /// EVENTS LIST END /////////////////////////////////////////////////

    /// START Coordinates Contain Check //
    std::function<bool(float, float)> contains = nullptr;

    ElementView *resetContainFn();

    template<class CallBackCheck = std::function<bool(float, float)>>
    ElementView *addContainsFn(CallBackCheck &&callBack);
    /// END Coordinates Contain Check //

private:
    /// CHAIN FOR DEFAULT STYLES
    std::function<void(ElementView *)> DrawStylesChain = nullptr;

    /// EVENTS CHAIN START
    TouchOverEventChain TouchOverEventChainValue;
    TouchLeaveEventChain TouchLeaveEventChainValue;

    TouchMoveEventChain TouchMoveEventChainValue;
    TouchDownEventChain TouchDownEventChainValue;
    TouchUpEventChain TouchUpEventChainValue;
    TouchEventChain TouchEventChainValue;

    KeyDownEventChain KeyDownEventChainValue;
    KeyUpEventChain KeyUpEventChainValue;
    KeyEventChain KeyEventChainValue;

    SetPaintsEventChain SetPaintsEventChainValue;

    AddChildEventChain AddChildEventChainValue;
    RemoveChildEventChain RemoveChildEventChainValue;
    ReplaceChildEventChain ReplaceChildEventChainValue;

    SetBackgroundColorEventChain SetBackgroundColorEventChainValue;

    UnmountOnThreeEventChain UnmountOnThreeEventChainValue;
    MountOnThreeEventChain MountOnThreeEventChainValue;

    DrawEventChain DrawEventChainValue;

    ResizeEventChain ResizeEventChainValue;
    /// EVENTS CHAIN END

    /// START DRAWER PRIVATE OPTIONS  //

    void SetEachPainters();

    template<typename PaintFunction, typename... Args>
    void SetEachPainters(PaintFunction paintCallback, Args... args);
    /// END DRAWER PRIVATE OPTIONS  //

    template<typename CallBackFunc>
    void callSafeOnMountThree(CallBackFunc callback);

protected:
    template<typename CallBackFunction, typename RemoveEventCallBack>
    void addChainFunction(CallBackFunction &chainFunc, CallBackFunction &callBack,
                          RemoveEventCallBack &removeChainFunction = nullptr,
                          bool startFromNewPoint = false, bool callAsync = true);

    //    template<typename ChainFunc, typename... Args>
    template<class ChainFunc, class... Args>
    void dispatchChainFunction(ChainFunc &chainFunc, Args &&...args);

    void InitCustomEventListeners();

    void drawMe() { return; };
};

#endif // CUDA_NEU_ELEMENTVIEW_H
