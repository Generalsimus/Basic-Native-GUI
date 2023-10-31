/// ELEMENT EVENTS LIST
/// ////////////////////////////////////////////////////////////////////////////////////////

#include "../utils/asyncTasks.cpp"
#include "elementView.h"

/// TOUCH OVER //
template<typename RemoveEventCallBack>
ElementView *
ElementView::addTouchOverEvent(TouchOverEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("RUN addTouchOverEvent()");
    //    auto rem = std::function([]() {});
    //  addChainFunction(TouchOverEventChain, callBack, removeEventCallBack,
    //                   TouchOverEventChain == nullptr, false);

    TouchOverEventChainValue.addNewAfter(std::forward<TouchOverEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
}

ElementView *ElementView::dispatchTouchOverEvent() {
    if (!this->isMouseOver) {
        this->isMouseOver = true;
        TouchOverEventChainValue.callAfter(this);

    }
    return this;
};

/// TOUCH LEAVE //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchLeaveEvent(TouchLeaveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack,
                                             bool isAsync) {
    // printf("RUN addTouchOverEvent()");

    //  addChainFunction(TouchLeaveEventChain, callBack, removeEventCallBack,
    //                   TouchLeaveEventChain == nullptr, true);
    TouchLeaveEventChainValue.addNewAfter(std::forward<TouchLeaveEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);

    return this;
}

ElementView *ElementView::dispatchTouchLeaveEvent() {
    // printf("RUN dispatchTouchLeaveEvent()\n");
    if (this->isMouseOver) {
        this->isMouseOver = false;
        TouchLeaveEventChainValue.callAfter(nullptr);

        for (auto &child: children) {
            child->dispatchTouchLeaveEvent();
        }
    }
    return this;
};

/// TOUCH MOVE //
template<typename RemoveEventCallBack>
ElementView *
ElementView::addTouchMoveEvent(TouchMoveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("RUN addTouchDownEvent()");

    //  addChainFunction(TouchMoveEventChain, callBack, removeEventCallBack,
    //                   TouchMoveEventChain == nullptr, true);

    TouchMoveEventChainValue.addNewAfter(std::forward<TouchMoveEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);

    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchMoveEvent(Args &&... args) {
    if (this->contains(std::forward<Args>(args)...)) {
        this->dispatchTouchOverEvent();

        //    dispatchChainFunction(TouchMoveEventChain, this, windowX, windowY);
        TouchMoveEventChainValue.callAfter(this, std::forward<Args>(args)...);

        for (auto &child: children) {
            child->dispatchTouchMoveEvent(std::forward<Args>(args)...);
        }
    } else {
//        for (auto &child: children) {
//            if (child->isMouseOver) {
//                child->dispatchTouchLeaveEvent();
//            }
////            child->dispatchTouchMoveEvent(std::forward<Args>(args)...);
//            child->dispatchTouchLeaveEvent();
//        }
        this->dispatchTouchLeaveEvent();
    }

    return this;
};

/// TOUCH DOWN //
template<typename RemoveEventCallBack>
ElementView *
ElementView::addTouchDownEvent(TouchDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {

    TouchDownEventChainValue.addNewAfter(std::forward<TouchDownEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchDownEvent(Args &&... args) {
    std::cout << "addTouchDownEvent\n" << std::endl;
    // printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

    if (this->isMouseOver) {

        TouchDownEventChainValue.callAfter(this, std::forward<Args>(args)...);
//        TouchDownEventChainValue.callAfter(this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchDownEvent(std::forward<Args>(args)...);
        }
    }
    return this;
};

/// TOUCH UP //
template<typename RemoveEventCallBack>
ElementView *
ElementView::addTouchUpEvent(TouchUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("RUN addTouchUpEvent()");

    //  addChainFunction(TouchUpEventChain, callBack, removeEventCallBack,
    //                   TouchUpEventChain == nullptr, true);

    TouchUpEventChainValue.addNewAfter(std::forward<TouchUpEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchUpEvent(Args &&... args) {
    // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

    if (this->isMouseOver) {
        //    dispatchChainFunction(TouchUpEventChain, this, windowX, windowY,
        //    typeIndex);
        TouchUpEventChainValue.callAfter(this, std::forward<Args>(args)...);

        for (auto &child: children) {
            child->dispatchTouchUpEvent(std::forward<Args>(args)...);
        }
    }
    return this;
};

/// TOUCH ///
template<typename RemoveEventCallBack>
ElementView *
ElementView::addTouchEvent(TouchEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("RUN addTouchEvent()");

    //  addChainFunction(TouchEventChain, callBack, removeEventCallBack,
    //                   TouchEventChain == nullptr, true);

    TouchEventChainValue.addNewAfter(std::forward<TouchEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);

    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchTouchEvent(Args &... args) {
    // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

    //    if (PositionIsOver(windowX, windowY)) {

    //  dispatchChainFunction(TouchEventChain, this, windowX, windowY, typeIndex);

    TouchEventChainValue.callAfter(this, std::forward<Args>(args)...);
    for (auto &child: children) {
        child->dispatchTouchEvent(args...);
    }
    //    }

    return this;
};

/// KEY DOWN //
template<typename RemoveEventCallBack>
ElementView *
ElementView::addKeyDownEvent(KeyDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("RUN addKeyDownEvent()");

    KeyDownEventChainValue.addNewAfter(std::forward<KeyDownEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    //  addChainFunction(KeyDownEventChain, callBack, removeEventCallBack,
    //                   KeyDownEventChain == nullptr, true);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchKeyDownEvent(Args &&... args) {

    //  dispatchChainFunction(KeyDownEventChain, this, keyIndex);

    KeyDownEventChainValue.callAfter(this, std::forward<Args>(args)...);
    //  KeyDownEventChain = KeyDownEventChain.addNewAfter(callBack, true);
    return this;
};

/// KEY Up //
template<typename RemoveEventCallBack>
ElementView *
ElementView::addKeyUpEvent(KeyUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("RUN addKeyUpEvent()");

    //  addChainFunction(KeyUpEventChain, callBack, removeEventCallBack,
    //                   KeyUpEventChain == nullptr, true);

    KeyUpEventChainValue.addNewAfter(std::forward<KeyUpEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchKeyUpEvent(Args &&... args) {

    //  dispatchChainFunction(KeyUpEventChain, this, keyIndex);
    KeyUpEventChainValue.callAfter(this, std::forward<Args>(args)...);

    return this;
};

/// KEY ///
template<typename RemoveEventCallBack>
ElementView *
ElementView::addKeyEvent(KeyEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("RUN addKeyDownEvent()");

    //  addChainFunction(KeyEventChain, callBack, removeEventCallBack,
    //                   KeyEventChain == nullptr, true);

    KeyEventChainValue.addNewAfter(std::forward<KeyEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
}

template<typename... Args>
ElementView *ElementView::dispatchKeyEvent(Args &&... args) {

    //  dispatchChainFunction(KeyEventChain, this, keyIndex);

    KeyEventChainValue.callAfter(this, std::forward<Args>(args)...);
    return this;
}

/// DRAW ///
template<typename RemoveEventCallBack>
ElementView *
ElementView::addDrawEvent(DrawEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    // printf("WINDOW ADD DRAWER\n");

    DrawEventChainValue.addNewAfter(std::forward<DrawEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchDrawEvent(Args &&... args) {
    // printf("RUNNNNNNNNN SS2\n");

    DrawEventChainValue.callAfter(this, std::forward<Args>(args)...);

    return this;
};

ElementView *ElementView::draw() {
    auto drawFunc = [](ElementView *element) {
        auto awaitProcess1 = CreateAsyncAwaitGroup();
        element->dispatchDrawEvent(element->window->surface->getCanvas(), &element->window->paint);
        awaitProcess1();

        auto awaitProcess2 = CreateAsyncAwaitGroup();
        for (auto &child: element->children) {
//            std::cout << "child IDDDDD: " << child->id << std::endl;
            child->dispatchDrawEvent(element->window->surface->getCanvas(), &element->window->paint);
        };
        awaitProcess2();

        element->window->refreshFrame();
    };
    if (this->window == nullptr) {
        std::function < void() > removeEvent = []() {

        };
        this->addMountOnThreeEvent([removeEvent, drawFunc](ElementView *element, ElementView *parentElement) mutable {
            removeEvent();
            drawFunc(element);
        }, removeEvent);
    } else {
        drawFunc(this);
    }

    return this;
};

/// Resize ///
template<typename RemoveEventCallBack>
ElementView *
ElementView::addResizeEvent(ResizeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    //  this->addChainFunction(ResizeEventChain, callBack, removeEventCallBack,
    //                         ResizeEventChain == nullptr, true);

    ResizeEventChainValue.addNewAfter(std::forward<ResizeEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchResizeEvent(Args &... args) {
    //  this->dispatchChainFunction(ResizeEventChain, this, elementWidth,
    //                              elementHeight);

    ResizeEventChainValue.callAfter(this, std::forward<Args>(args)...);

    return this;
};

/// Set Paints ///
template<typename RemoveEventCallBack>
ElementView *
ElementView::addSetPaintsEvent(SetPaintsEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    //  addChainFunction(SetPaintsEventChain, callBack, removeEventCallBack,
    //                   SetPaintsEventChain == nullptr, true);
    SetPaintsEventChainValue.addNewAfter(std::forward<SetPaintsEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
};

ElementView *ElementView::dispatchSetPaintsEvent() {
    //  dispatchChainFunction(SetPaintsEventChain, this);

    SetPaintsEventChainValue.callAfter(this);
    return this;
};

/// ADD CHILD
template<typename RemoveEventCallBack>
ElementView *
ElementView::addAddChildEvent(AddChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack, bool isAsync) {

    //  addChainFunction(AddChildEventChain, callBack, removeEventCallBack,
    //                   AddChildEventChain == nullptr, true);

    AddChildEventChainValue.addNewAfter(std::forward<AddChildEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchAddChildEvent(Args &... args) {
    //  dispatchChainFunction(AddChildEventChain, this, newChild);

    AddChildEventChainValue.callAfter(this, std::forward<Args>(args)...);
    return this;
};

/// REMOVE CHILD
template<typename RemoveEventCallBack>
ElementView *
ElementView::addRemoveChildEvent(RemoveChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack,
                                 bool isAsync) {
    //  addChainFunction(RemoveChildEventChain, callBack, removeEventCallBack,
    //                   RemoveChildEventChain == nullptr, true);

    RemoveChildEventChainValue.addNewAfter(std::forward<RemoveChildEventType>(callBack), isAsync)->invokeRemoveFunction(
            removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchRemoveChildEvent(Args &... args) {
    //  dispatchChainFunction(RemoveChildEventChain, this, removeIndex, count);

    RemoveChildEventChainValue.callAfter(this, std::forward<Args>(args)...);
    return this;
};

/// REPLACE CHILD
template<typename RemoveEventCallBack>
ElementView *
ElementView::addReplaceChildEvent(ReplaceChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack,
                                  bool isAsync) {
    //  addChainFunction(ReplaceChildEventChain, callBack, removeEventCallBack,
    //                   ReplaceChildEventChain == nullptr, true);

    ReplaceChildEventChainValue.addNewAfter(std::forward<ReplaceChildEventType>(callBack),
                                            isAsync)->invokeRemoveFunction(removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchReplaceChildEvent(Args &... args) {
    //  dispatchChainFunction(ReplaceChildEventChain, this, replaceIndex,
    //  oldChild,
    //                        newChild);

    ReplaceChildEventChainValue.callAfter(this, std::forward<Args>(args)...);
    return this;
};

/// SetBackground
template<typename RemoveEventCallBack>
ElementView *ElementView::addSetBackgroundColorEvent(SetBackgroundColorEventType &&callBack,
                                                     RemoveEventCallBack &&removeEventCallBack, bool isAsync) {
    //  addChainFunction(SetBackgroundColorEventChain, callBack,
    //  removeEventCallBack,
    //                   SetBackgroundColorEventChain == nullptr, true);

    SetBackgroundColorEventChainValue.addNewAfter(std::forward<SetBackgroundColorEventType>(callBack),
                                                  true)->invokeRemoveFunction(removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchSetBackgroundColorEvent(Args &&... args) {
    //  auto asyncAwaitGroup = CreateAsyncAwaitGroup();
    //  dispatchChainFunction(SetBackgroundColorEventChain, this, newColor);

    SetBackgroundColorEventChainValue.callAfter(this, std::forward<Args>(args)...);
    //  asyncAwaitGroup();
    return this;
};

/// MountOnThree
template<typename RemoveEventCallBack>
ElementView *
ElementView::addMountOnThreeEvent(MountOnThreeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack,
                                  bool isAsync) {

    MountOnThreeEventChainValue.addNewAfter(std::forward<MountOnThreeEventType>(callBack),
                                            isAsync)->invokeRemoveFunction(removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchMountOnThreeEvent(Args &&... args) {
    printf("RUN RUN MOUNT CHAINT\n");
    MountOnThreeEventChainValue.callAfter(this, std::forward<Args>(args)...);
    return this;
};

/// UnmountOnThree
template<typename RemoveEventCallBack>
ElementView *
ElementView::addUnmountOnThreeEvent(UnmountOnThreeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack,
                                    bool isAsync) {

    UnmountOnThreeEventChainValue.addNewAfter(std::forward<UnmountOnThreeEventType>(callBack),
                                              true)->invokeRemoveFunction(removeEventCallBack);
    return this;
};

template<typename... Args>
ElementView *ElementView::dispatchUnmountOnThreeEvent(Args &&... args) {
    UnmountOnThreeEventChainValue.callAfter(this, std::forward<Args>(args)...);
    return this;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
