
/// ELEMENT EVENTS LIST ////////////////////////////////////////////////////////////////////////////////////////

#include "elementView.h"
#include "../utils/asyncTasks.cpp"

/// TOUCH OVER //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchOverEvent(TouchOverEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
   // printf("RUN addTouchOverEvent()");
//    auto rem = std::function([]() {});
    addChainFunction(TouchOverEventChain, callBack, removeEventCallBack, TouchOverEventChain == nullptr, false);

    return this;
}

ElementView *ElementView::dispatchTouchOverEvent() {
    if (!this->isMouseOver) {
        this->isMouseOver = true;

        dispatchChainFunction(TouchOverEventChain, this);

    }
    return this;
};

/// TOUCH LEAVE //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchLeaveEvent(TouchLeaveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
   // printf("RUN addTouchOverEvent()");

    addChainFunction(TouchLeaveEventChain, callBack, removeEventCallBack, TouchLeaveEventChain == nullptr, true);


    return this;
}

ElementView *ElementView::dispatchTouchLeaveEvent() {
    // printf("RUN dispatchTouchLeaveEvent()\n");
    if (this->isMouseOver) {
        this->isMouseOver = false;
        dispatchChainFunction(TouchLeaveEventChain, this);

        for (auto &child: children) {
            child->dispatchTouchLeaveEvent();
        }
    }
    return this;
};

/// TOUCH MOVE //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchMoveEvent(TouchMoveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchDownEvent()");

    addChainFunction(TouchMoveEventChain, callBack, removeEventCallBack, TouchMoveEventChain == nullptr, true);

    return this;
}


ElementView *ElementView::dispatchTouchMoveEvent(float windowX, float windowY, bool isAsync, bool useTouchOverChild) {
//    printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

    if (this->isMouseOver) {
        dispatchChainFunction(TouchMoveEventChain, this, windowX, windowY);

//        for (auto &child: children) {
//            child->dispatchTouchMoveEvent(windowX, windowY);
//        }
    }
    return this;
};


/// TOUCH DOWN //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchDownEvent(TouchDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchDownEvent()");

    addChainFunction(TouchDownEventChain, callBack, removeEventCallBack, TouchDownEventChain == nullptr, true);

    return this;
}


ElementView *ElementView::dispatchTouchDownEvent(float windowX, float windowY, int typeIndex) {
    // printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

    if (this->isMouseOver) {
        dispatchChainFunction(TouchDownEventChain, this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchDownEvent(windowX, windowY, typeIndex);
        }
    }
    return this;
};


/// TOUCH UP //
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchUpEvent(TouchUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchUpEvent()");

    addChainFunction(TouchUpEventChain, callBack, removeEventCallBack, TouchUpEventChain == nullptr, true);

    return this;
}


ElementView *ElementView::dispatchTouchUpEvent(float windowX, float windowY, int typeIndex) {
   // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

    if (this->isMouseOver) {
        dispatchChainFunction(TouchUpEventChain, this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchUpEvent(windowX, windowY, typeIndex);
        }
    }
    return this;
};

/// TOUCH ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addTouchEvent(TouchEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    // printf("RUN addTouchEvent()");

    addChainFunction(TouchEventChain, callBack, removeEventCallBack, TouchEventChain == nullptr, true);

    return this;
}


ElementView *ElementView::dispatchTouchEvent(float windowX, float windowY, int typeIndex) {
   // printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

//    if (PositionIsOver(windowX, windowY)) {

        dispatchChainFunction(TouchEventChain, this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchEvent(windowX, windowY, typeIndex);
        }
//    }

    return this;
};

/// KEY DOWN //
template<typename RemoveEventCallBack>
ElementView *ElementView::addKeyDownEvent(KeyDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
   // printf("RUN addKeyDownEvent()");

    addChainFunction(KeyDownEventChain, callBack, removeEventCallBack, KeyDownEventChain == nullptr, true);
    return this;
}

ElementView *ElementView::dispatchKeyDownEvent(int keyIndex) {

    dispatchChainFunction(KeyDownEventChain, this, keyIndex);

    return this;
};

/// KEY Up //
template<typename RemoveEventCallBack>
ElementView *ElementView::addKeyUpEvent(KeyUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
   // printf("RUN addKeyUpEvent()");

    addChainFunction(KeyUpEventChain, callBack, removeEventCallBack, KeyUpEventChain == nullptr, true);
    return this;
}

ElementView *ElementView::dispatchKeyUpEvent(int keyIndex) {

    dispatchChainFunction(KeyUpEventChain, this, keyIndex);

    return this;
};

/// KEY ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addKeyEvent(KeyEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
   // printf("RUN addKeyDownEvent()");

    addChainFunction(KeyEventChain, callBack, removeEventCallBack, KeyEventChain == nullptr, true);
    return this;
}

ElementView *ElementView::dispatchKeyEvent(int keyIndex) {

    dispatchChainFunction(KeyEventChain, this, keyIndex);

    return this;
}

/// DRAW ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addDrawEvent(DrawEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
   // printf("WINDOW ADD DRAWER\n");

    this->addChainFunction(DrawEventChain, callBack, removeEventCallBack, DrawEventChain == nullptr, false);
    return this;
};

ElementView *ElementView::dispatchDrawEvent() {
//    printf("RUNNNNNNNNN SS2\n");
    if (this->window == nullptr) {
        std::function < void() > removeEvent = []() {

        };
        this->addMountOnThreeEvent([removeEvent](ElementView *element, ElementView *parentElement) mutable {
            element->dispatchHierarchyDrawEvent(element->window->surface->getCanvas(), &element->window->paint);
//            element->window->refreshFrame();

            removeEvent();
        }, removeEvent);
    } else {
        this->dispatchHierarchyDrawEvent(this->window->surface->getCanvas(), &this->window->paint);
//        this->window->refreshFrame();
    }


    return this;
};

ElementView *ElementView::dispatchHierarchyDrawEvent(SkCanvas *canvas, SkPaint *painter) {
    //printf("RUNNNNNNNNN SS2\n");
    this->dispatchChainFunction(DrawEventChain, this, canvas, painter);
    for (auto &child: children) {
        child->dispatchHierarchyDrawEvent(canvas, painter);
    }
    return this;
};


/// Resize ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addResizeEvent(ResizeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    this->addChainFunction(ResizeEventChain, callBack, removeEventCallBack, ResizeEventChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchResizeEvent(float newWidth, float newHeight) {
    this->dispatchChainFunction(ResizeEventChain, this, newWidth, newHeight);

    return this;
};

/// Set Paints ///
template<typename RemoveEventCallBack>
ElementView *ElementView::addSetPaintsEvent(SetPaintsEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(SetPaintsEventChain, callBack, removeEventCallBack, SetPaintsEventChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchSetPaintsEvent() {
    dispatchChainFunction(SetPaintsEventChain, this);
    return this;
};

/// ADD CHILD
template<typename RemoveEventCallBack>
ElementView *ElementView::addAddChildEvent(AddChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {

    addChainFunction(AddChildEventChain, callBack, removeEventCallBack, AddChildEventChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchAddChildEvent(ElementView *newChild) {
    dispatchChainFunction(AddChildEventChain, this, newChild);
    return this;
};

/// REMOVE CHILD
template<typename RemoveEventCallBack>
ElementView *
ElementView::addRemoveChildEvent(RemoveChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(RemoveChildEventChain, callBack, removeEventCallBack, RemoveChildEventChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchRemoveChildEvent(int removeIndex, int count) {
    dispatchChainFunction(RemoveChildEventChain, this, removeIndex, count);
    return this;
};


/// REPLACE CHILD
template<typename RemoveEventCallBack>
ElementView *
ElementView::addReplaceChildEvent(ReplaceChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(ReplaceChildEventChain, callBack, removeEventCallBack, ReplaceChildEventChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchReplaceChildEvent(int replaceIndex, ElementView *oldChild, ElementView *newChild) {
    dispatchChainFunction(ReplaceChildEventChain, this, replaceIndex, oldChild, newChild);
    return this;
};


/// SetBackground
template<typename RemoveEventCallBack>
ElementView *ElementView::addSetBackgroundColorEvent(SetBackgroundColorEventType &&callBack,
                                                     RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(SetBackgroundColorEventChain, callBack, removeEventCallBack,
                     SetBackgroundColorEventChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchSetBackgroundColorEvent(SkColor newColor) {
    auto asyncAwaitGroup = CreateAsyncAwaitGroup();
    dispatchChainFunction(SetBackgroundColorEventChain, this, newColor);
    asyncAwaitGroup();
    return this;
};

/// MountOnThree
template<typename RemoveEventCallBack>
ElementView *
ElementView::addMountOnThreeEvent(MountOnThreeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(MountOnThreeEventChain, callBack, removeEventCallBack, MountOnThreeEventChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchMountOnThreeEvent(ElementView *parentElement) {
    dispatchChainFunction(MountOnThreeEventChain, this, parentElement);
    return this;
};

/// UnmountOnThree
template<typename RemoveEventCallBack>
ElementView *
ElementView::addUnmountOnThreeEvent(UnmountOnThreeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(UnmountOnThreeChain, callBack, removeEventCallBack, UnmountOnThreeChain == nullptr, true);
    return this;
};

ElementView *ElementView::dispatchUnmountOnThreeEvent(ElementView *parentElement) {
    dispatchChainFunction(UnmountOnThreeChain, this, parentElement);
    return this;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// WINDOW EVENTS LIST ////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////