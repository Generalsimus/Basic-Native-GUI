
/// ELEMENT EVENTS LIST
/// ////////////////////////////////////////////////////////////////////////////////////////

#include "../utils/asyncTasks.cpp"
#include "elementView.h"

/// TOUCH OVER //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchOverEvent(TouchOverEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchOverEvent()");
    //    auto rem = std::function([]() {});
    //  addChainFunction(TouchOverEventChain, callBack, removeEventCallBack,
    //                   TouchOverEventChain == nullptr, false);

    TouchOverEventChainValue.addNewAfter(std::forward<TouchOverEventType>(callBack), true);
    return this;
}

ElementView *ElementView::dispatchTouchOverEvent() {
    if (!this->isMouseOver) {
        this->isMouseOver = true;
        TouchOverEventChainValue.callBefore(this);
    }
    return this;
};

/// TOUCH LEAVE //
template<typename RemoveEventCallBack>
ElementView *
ElementView::addTouchLeaveEvent(TouchLeaveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchOverEvent()");

    //  addChainFunction(TouchLeaveEventChain, callBack, removeEventCallBack,
    //                   TouchLeaveEventChain == nullptr, true);
    TouchLeaveEventChainValue.addNewAfter(std::forward<TouchLeaveEventType>(callBack), true);

    return this;
}

ElementView *ElementView::dispatchTouchLeaveEvent() {
    // printf("RUN dispatchTouchLeaveEvent()\n");
    if (this->isMouseOver) {
        this->isMouseOver = false;
        TouchLeaveEventChainValue.callBefore(nullptr);

        for (auto &child: children) {
            child->dispatchTouchLeaveEvent();
        }
    }
    return this;
};

/// TOUCH MOVE //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchMoveEvent(TouchMoveEventType &&callBack,
                                            RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchDownEvent()");

    //  addChainFunction(TouchMoveEventChain, callBack, removeEventCallBack,
    //                   TouchMoveEventChain == nullptr, true);

    TouchMoveEventChainValue.addNewAfter(std::forward<TouchMoveEventType>(callBack), true);

    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchMoveEvent(Args &&... args) {

    //    printf("addContainsFn %.3f %.3f \n",windowX, windowY);

    if (this->contains(std::forward<Args>(args)...)) {
        this->dispatchTouchOverEvent();

        //    dispatchChainFunction(TouchMoveEventChain, this, windowX, windowY);
        TouchMoveEventChainValue.callBefore(this, std::forward<Args>(args)...);

        for (auto &child: children) {
            child->dispatchTouchMoveEvent(std::forward<Args>(args)...);
        }
    }

    return this;
};

/// TOUCH DOWN //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchDownEvent(TouchDownEventType &&callBack,
                                            RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchDownEvent()");

    //  addChainFunction(TouchDownEventChain, callBack, removeEventCallBack,
    //                   TouchDownEventChain == nullptr, true);

    TouchDownEventChainValue.addNewAfter(std::forward<TouchDownEventType>(callBack), true);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchDownEvent(Args &&... args) {
    // printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

    if (this->isMouseOver) {
        //    dispatchChainFunction(TouchDownEventChain, this, windowX, windowY,
        //                          typeIndex);

        TouchDownEventChainValue.callBefore(this, std::forward<Args>(args)...);
//        TouchDownEventChainValue.callBefore(this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchDownEvent(std::forward<Args>(args)...);
        }
    }
    return this;
};

/// TOUCH UP //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchUpEvent(TouchUpEventType &&callBack,
                                          RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchUpEvent()");

    //  addChainFunction(TouchUpEventChain, callBack, removeEventCallBack,
    //                   TouchUpEventChain == nullptr, true);

    TouchUpEventChainValue.addNewAfter(std::forward<TouchUpEventType>(callBack), true);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchUpEvent(Args &&... args) {
    // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

    if (this->isMouseOver) {
        //    dispatchChainFunction(TouchUpEventChain, this, windowX, windowY,
        //    typeIndex);
        TouchUpEventChainValue.callBefore(this, std::forward<Args>(args)...);

        for (auto &child: children) {
            child->dispatchTouchUpEvent(std::forward<Args>(args)...);
        }
    }
    return this;
};

/// TOUCH ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchEvent(TouchEventType &&callBack,
                                        RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchEvent()");

    //  addChainFunction(TouchEventChain, callBack, removeEventCallBack,
    //                   TouchEventChain == nullptr, true);

    TouchEventChainValue.addNewAfter(std::forward<TouchEventType>(callBack), true);

    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchEvent(Args &... args) {
    // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

    //    if (PositionIsOver(windowX, windowY)) {

    //  dispatchChainFunction(TouchEventChain, this, windowX, windowY, typeIndex);

    TouchEventChainValue.callBefore(this, std::forward<Args>(args)...);
    for (auto &child: children) {
        child->dispatchTouchEvent(args...);
    }
    //    }

    return this;
};

/// KEY DOWN //
template<typename RemoveEventCallBack>
ElementView *ElementView::addKeyDownEvent(KeyDownEventType &&callBack,
                                          RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addKeyDownEvent()");

    KeyDownEventChainValue.addNewAfter(std::forward<KeyDownEventType>(callBack), true);
    //  addChainFunction(KeyDownEventChain, callBack, removeEventCallBack,
    //                   KeyDownEventChain == nullptr, true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchKeyDownEvent(Args &&... args) {

    //  dispatchChainFunction(KeyDownEventChain, this, keyIndex);

    KeyDownEventChainValue.callBefore(this, std::forward<Args>(args)...);
    //  KeyDownEventChain = KeyDownEventChain.addNewAfter(callBack, true);
    return this;
};

/// KEY Up //
template<typename RemoveEventCallBack>
ElementView *ElementView::addKeyUpEvent(KeyUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addKeyUpEvent()");

    //  addChainFunction(KeyUpEventChain, callBack, removeEventCallBack,
    //                   KeyUpEventChain == nullptr, true);

    KeyUpEventChainValue.addNewAfter(std::forward<KeyUpEventType>(callBack), true);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchKeyUpEvent(Args &&... args) {

    //  dispatchChainFunction(KeyUpEventChain, this, keyIndex);
    KeyUpEventChainValue.callBefore(this, std::forward<Args>(args)...);

    return this;
};

/// KEY ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addKeyEvent(KeyEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addKeyDownEvent()");

    //  addChainFunction(KeyEventChain, callBack, removeEventCallBack,
    //                   KeyEventChain == nullptr, true);

    KeyEventChainValue.addNewAfter(std::forward<KeyEventType>(callBack), true);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchKeyEvent(Args &&... args) {

    //  dispatchChainFunction(KeyEventChain, this, keyIndex);

    KeyEventChainValue.callBefore(this, std::forward<Args>(args)...);
    return this;
}

/// DRAW ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addDrawEvent(DrawEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("WINDOW ADD DRAWER\n");

    //  this->addChainFunction(DrawEventChain, callBack, removeEventCallBack,
    //                         DrawEventChain == nullptr, false);

    DrawEventChainValue.addNewAfter(std::forward<DrawEventType>(callBack), true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchDrawEvent(Args &&... args) {
    // printf("RUNNNNNNNNN SS2\n");
    //  this->dispatchChainFunction(DrawEventChain, this, canvas, painter);

    DrawEventChainValue.callBefore(this, std::forward<Args>(args)...);
    for (auto &child: children) {
        child->dispatchDrawEvent(std::forward<Args>(args)...);
    }
    return this;
};

ElementView *ElementView::draw() {
    return this;
    //    printf("RUNNNNNNNNN SS2\n");
    //  auto awaitProcess2 = CreateAsyncAwaitGroup();
    //  //    auto awaitProcess = CreateAsyncAwaitGroup();
    //  if (this->window == nullptr) {
    //    std::function<void()> removeEvent = []() {
    //
    //    };
    //    this->addMountOnThreeEvent(
    //        [removeEvent](ElementView *element,
    //                      ElementView *parentElement) mutable {
    //          element->dispatchDrawEvent(element->window->surface->getCanvas(),
    //                                     &element->window->paint);
    //          //            element->window->refreshFrame();
    //
    //          removeEvent();
    //        },
    //        removeEvent);
    //  } else {
    //
    //    this->dispatchDrawEvent(this->window->surface->getCanvas(),
    //                            &this->window->paint);
    //    //        this->window->refreshFrame();
    //  }
    //
    //  awaitProcess2();
    return this;
};

/// Resize ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addResizeEvent(ResizeEventType &&callBack,
                                         RemoveEventCallBack &&removeEventCallBack) {
    //  this->addChainFunction(ResizeEventChain, callBack, removeEventCallBack,
    //                         ResizeEventChain == nullptr, true);

    ResizeEventChainValue.addNewAfter(std::forward<ResizeEventType>(callBack), true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchResizeEvent(Args &... args) {
    //  this->dispatchChainFunction(ResizeEventChain, this, elementWidth,
    //                              elementHeight);

    ResizeEventChainValue.callBefore(this, std::forward<Args>(args)...);

    return this;
};

/// Set Paints ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addSetPaintsEvent(SetPaintsEventType &&callBack,
                                            RemoveEventCallBack &&removeEventCallBack) {
    //  addChainFunction(SetPaintsEventChain, callBack, removeEventCallBack,
    //                   SetPaintsEventChain == nullptr, true);
    SetPaintsEventChainValue.addNewAfter(std::forward<SetPaintsEventType>(callBack), true);
    return this;
};

ElementView *ElementView::dispatchSetPaintsEvent() {
    //  dispatchChainFunction(SetPaintsEventChain, this);

    SetPaintsEventChainValue.callBefore(this);
    return this;
};

/// ADD CHILD
template<typename RemoveEventCallBack>
ElementView *ElementView::addAddChildEvent(AddChildEventType &&callBack,
                                           RemoveEventCallBack &&removeEventCallBack) {

    //  addChainFunction(AddChildEventChain, callBack, removeEventCallBack,
    //                   AddChildEventChain == nullptr, true);

    AddChildEventChainValue.addNewAfter(std::forward<AddChildEventType>(callBack), true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchAddChildEvent(Args &... args) {
    //  dispatchChainFunction(AddChildEventChain, this, newChild);

    AddChildEventChainValue.callBefore(this, std::forward<Args>(args)...);
    return this;
};

/// REMOVE CHILD
template<typename RemoveEventCallBack>
ElementView *ElementView::addRemoveChildEvent(RemoveChildEventType &&callBack,
                                              RemoveEventCallBack &&removeEventCallBack) {
    //  addChainFunction(RemoveChildEventChain, callBack, removeEventCallBack,
    //                   RemoveChildEventChain == nullptr, true);

    RemoveChildEventChainValue.addNewAfter(std::forward<RemoveChildEventType>(callBack), true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchRemoveChildEvent(Args &... args) {
    //  dispatchChainFunction(RemoveChildEventChain, this, removeIndex, count);

    RemoveChildEventChainValue.callBefore(this, std::forward<Args>(args)...);
    return this;
};

/// REPLACE CHILD
template<typename RemoveEventCallBack>
ElementView *ElementView::addReplaceChildEvent(ReplaceChildEventType &&callBack,
                                               RemoveEventCallBack &&removeEventCallBack) {
    //  addChainFunction(ReplaceChildEventChain, callBack, removeEventCallBack,
    //                   ReplaceChildEventChain == nullptr, true);

    ReplaceChildEventChainValue.addNewAfter(std::forward<ReplaceChildEventType>(callBack), true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchReplaceChildEvent(Args &... args) {
    //  dispatchChainFunction(ReplaceChildEventChain, this, replaceIndex,
    //  oldChild,
    //                        newChild);

    ReplaceChildEventChainValue.callBefore(this, std::forward<Args>(args)...);
    return this;
};

/// SetBackground
template<typename RemoveEventCallBack>
ElementView *ElementView::addSetBackgroundColorEvent(SetBackgroundColorEventType &&callBack,
                                                     RemoveEventCallBack &&removeEventCallBack) {
    //  addChainFunction(SetBackgroundColorEventChain, callBack,
    //  removeEventCallBack,
    //                   SetBackgroundColorEventChain == nullptr, true);

    SetBackgroundColorEventChainValue.addNewAfter(std::forward<SetBackgroundColorEventType>(callBack), true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchSetBackgroundColorEvent(Args &&... args) {
    //  auto asyncAwaitGroup = CreateAsyncAwaitGroup();
    //  dispatchChainFunction(SetBackgroundColorEventChain, this, newColor);

    SetBackgroundColorEventChainValue.callBefore(this, std::forward<Args>(args)...);
    //  asyncAwaitGroup();
    return this;
};

/// MountOnThree
template<typename RemoveEventCallBack>
ElementView *ElementView::addMountOnThreeEvent(MountOnThreeEventType &&callBack,
                                               RemoveEventCallBack &&removeEventCallBack) {
    //    MountOnThreeEventType chainEl = MountOnThreeEventType(callBack,true);

    MountOnThreeEventChainValue.addNewAfter(std::forward<MountOnThreeEventType>(callBack), true);;
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchMountOnThreeEvent(Args &&... args) {
    printf("RUN RUN MOUNT CHAINT\n");
    MountOnThreeEventChainValue.callBefore(this, std::forward<Args>(args)...);
    return this;
};

/// UnmountOnThree
template<typename RemoveEventCallBack>
ElementView *ElementView::addUnmountOnThreeEvent(UnmountOnThreeEventType &&callBack,
                                                 RemoveEventCallBack &&removeEventCallBack) {

    UnmountOnThreeEventChainValue.addNewAfter(std::forward<UnmountOnThreeEventType>(callBack), true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchUnmountOnThreeEvent(Args &&... args) {
    UnmountOnThreeEventChainValue.callBefore(this, std::forward<Args>(args)...);
    return this;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
