//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_ELEMENTVIEW_H
#define CUDA_NEU_ELEMENTVIEW_H

#include "functional"
#include "Windows.h"
#include "string"
#include <cstddef>
#include <vector>
#include <future>
#include "include/core/SkPaint.h"
#include "include/core/SkCanvas.h"
#include "./eventsType.h"


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
    ElementView *addTouchMoveEvent(TouchMoveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *
    dispatchTouchMoveEvent(float windowX, float windowY, bool isAsync = true, bool useTouchOverChild = true);

    /// TOUCH OVER
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchOverEvent(TouchOverEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchTouchOverEvent();

    /// TOUCH LEAVE
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *
    addTouchLeaveEvent(TouchLeaveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchTouchLeaveEvent();

    /// TOUCH DOWN
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchDownEvent(TouchDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchTouchDownEvent(float windowX, float windowY, int typeIndex);

    /// TOUCH UP
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchUpEvent(TouchUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchTouchUpEvent(float windowX, float windowY, int typeIndex);

    /// TOUCH
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addTouchEvent(TouchEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchTouchEvent(float windowX, float windowY, int typeIndex);

    /// KEY DOWN
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addKeyDownEvent(KeyDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchKeyDownEvent(int keyIndex);

    /// KEY Up
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addKeyUpEvent(KeyUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchKeyUpEvent(int keyIndex);

    /// KEY
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addKeyEvent(KeyEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchKeyEvent(int keyIndex);

    /// Draw
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addDrawEvent(DrawEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchDrawEvent();

    ElementView *dispatchHierarchyDrawEvent(SkCanvas *canvas, SkPaint *paint);

    /// RESIZE ELEMENT
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addResizeEvent(ResizeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchResizeEvent(float windowWidth, float windowHeight);


    /// Set Paints
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addSetPaintsEvent(SetPaintsEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchSetPaintsEvent();

    /// ADD CHILD
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addAddChildEvent(AddChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchAddChildEvent(ElementView *newChild);

    /// REMOVE CHILD
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *
    addRemoveChildEvent(RemoveChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchRemoveChildEvent(int removeIndex, int count = 1);


    /// REPLACE CHILD
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *
    addReplaceChildEvent(ReplaceChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchReplaceChildEvent(int replaceIndex, ElementView *oldChild, ElementView *newChild);

    /// SetBackground
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *addSetBackgroundColorEvent(SetBackgroundColorEventType &&callBack,
                                            RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchSetBackgroundColorEvent(SkColor newColor);

    /// MountOnThree
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *
    addMountOnThreeEvent(MountOnThreeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchMountOnThreeEvent(ElementView *parentElement);

    /// UnmountOnThree
    template<typename RemoveEventCallBack = std::function<void()>>
    ElementView *
    addUnmountOnThreeEvent(UnmountOnThreeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    ElementView *dispatchUnmountOnThreeEvent(ElementView *parentElement);

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
    TouchOverEventType TouchOverEventChain = nullptr;
    TouchLeaveEventType TouchLeaveEventChain = nullptr;

    TouchMoveEventType TouchMoveEventChain = nullptr;
    TouchDownEventType TouchDownEventChain = nullptr;
    TouchUpEventType TouchUpEventChain = nullptr;
    TouchEventType TouchEventChain = nullptr;

    KeyDownEventType KeyDownEventChain = nullptr;
    KeyUpEventType KeyUpEventChain = nullptr;
    KeyEventType KeyEventChain = nullptr;

    SetPaintsEventType SetPaintsEventChain = nullptr;


    AddChildEventType AddChildEventChain = nullptr;
    RemoveChildEventType RemoveChildEventChain = nullptr;
    ReplaceChildEventType ReplaceChildEventChain = nullptr;


    SetBackgroundColorEventType SetBackgroundColorEventChain = nullptr;

    UnmountOnThreeEventType UnmountOnThreeChain = nullptr;
    MountOnThreeEventType MountOnThreeEventChain = nullptr;

    DrawEventType DrawEventChain = nullptr;


    ResizeEventType ResizeEventChain = nullptr;
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


#endif //CUDA_NEU_ELEMENTVIEW_H
