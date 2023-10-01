
/// EVENTS LIST ////////////////////////////////////////////////////////////////////////////////////////

#include "element.h"

/// TOUCH OVER //
template<typename RemoveEventCallBack>
Element *Element::addTouchOverEvent(TouchOverEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addTouchOverEvent()");
//    auto rem = std::function([]() {});
    addChainFunction(TouchOverEventChain, callBack, removeEventCallBack, TouchOverEventChain == nullptr, false);

    return this;
}

Element *Element::dispatchTouchOverEvent() {
    if (!this->isMouseOver) {
        printf("RUN dispatchTouchOverEvent() \n");
        this->isMouseOver = true;

//    if (!this->isMouseOver) {
        dispatchChainFunction(TouchOverEventChain, this);

        for (auto &child: children) {
            child->dispatchTouchOverEvent();
        }
    }
    return this;
};

/// TOUCH LEAVE //
template<typename RemoveEventCallBack>
Element *Element::addTouchLeaveEvent(TouchLeaveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addTouchOverEvent()");

    addChainFunction(TouchLeaveEventChain, callBack, removeEventCallBack, TouchLeaveEventChain == nullptr, true);


    return this;
}

Element *Element::dispatchTouchLeaveEvent() {
    printf("RUN dispatchTouchLeaveEvent()\n");
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
Element *Element::addTouchMoveEvent(TouchMoveEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addTouchDownEvent()");

    addChainFunction(TouchMoveEventChain, callBack, removeEventCallBack, TouchMoveEventChain == nullptr, true);

    return this;
}


Element *Element::dispatchTouchMoveEvent(int windowX, int windowY, bool isAsync, bool useTouchOverChild) {
//    printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

    if (PositionIsOver(windowX, windowY)) {
        dispatchChainFunction(TouchMoveEventChain, this, windowX, windowY);

        for (auto &child: children) {
            child->dispatchTouchMoveEvent(windowX, windowY);
        }
    }
    return this;
};


/// TOUCH DOWN //
template<typename RemoveEventCallBack>
Element *Element::addTouchDownEvent(TouchDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addTouchDownEvent()");

    addChainFunction(TouchDownEventChain, callBack, removeEventCallBack, TouchDownEventChain == nullptr, true);

    return this;
}


Element *Element::dispatchTouchDownEvent(int windowX, int windowY, int typeIndex) {
    printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

    if (PositionIsOver(windowX, windowY)) {
        dispatchChainFunction(TouchDownEventChain, this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchDownEvent(windowX, windowY, typeIndex);
        }
    }
    return this;
};


/// TOUCH UP //
template<typename RemoveEventCallBack>
Element *Element::addTouchUpEvent(TouchUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addTouchUpEvent()");

    addChainFunction(TouchUpEventChain, callBack, removeEventCallBack, TouchUpEventChain == nullptr, true);

    return this;
}


Element *Element::dispatchTouchUpEvent(int windowX, int windowY, int typeIndex) {
    printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

    if (PositionIsOver(windowX, windowY)) {
        dispatchChainFunction(TouchUpEventChain, this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchUpEvent(windowX, windowY, typeIndex);
        }
    }
    return this;
};

/// TOUCH ///
template<typename RemoveEventCallBack>
Element *Element::addTouchEvent(TouchEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addTouchEvent()");

    addChainFunction(TouchEventChain, callBack, removeEventCallBack, TouchEventChain == nullptr, true);

    return this;
}


Element *Element::dispatchTouchEvent(int windowX, int windowY, int typeIndex) {
    printf("RUN dispatchTouchUpEvent() X:%d, Y: %d \n", windowX, windowY);

    if (PositionIsOver(windowX, windowY)) {

        dispatchChainFunction(TouchEventChain, this, windowX, windowY, typeIndex);

        for (auto &child: children) {
            child->dispatchTouchEvent(windowX, windowY, typeIndex);
        }
    }

    return this;
};

/// KEY DOWN //
template<typename RemoveEventCallBack>
Element *Element::addKeyDownEvent(KeyDownEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addKeyDownEvent()");

    addChainFunction(KeyDownEventChain, callBack, removeEventCallBack, KeyDownEventChain == nullptr, true);
    return this;
}

Element *Element::dispatchKeyDownEvent(int keyIndex) {

    dispatchChainFunction(KeyDownEventChain, this, keyIndex);

    return this;
};

/// KEY Up //
template<typename RemoveEventCallBack>
Element *Element::addKeyUpEvent(KeyUpEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addKeyUpEvent()");

    addChainFunction(KeyUpEventChain, callBack, removeEventCallBack, KeyUpEventChain == nullptr, true);
    return this;
}

Element *Element::dispatchKeyUpEvent(int keyIndex) {

    dispatchChainFunction(KeyUpEventChain, this, keyIndex);

    return this;
};

/*
 *
 *
 * */
/// KEY ///
template<typename RemoveEventCallBack>
Element *Element::addKeyEvent(KeyEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    printf("RUN addKeyDownEvent()");

    addChainFunction(KeyEventChain, callBack, removeEventCallBack, KeyEventChain == nullptr, true);
    return this;
}

Element *Element::dispatchKeyEvent(int keyIndex) {

    dispatchChainFunction(KeyEventChain, this, keyIndex);

    return this;
}

/// DRAW ///
template<typename RemoveEventCallBack>
Element *Element::addDrawEvent(DrawEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(DrawEventChain, callBack, removeEventCallBack, DrawEventChain == nullptr, true);
    return this;
};

Element *Element::dispatchDrawEvent(SkCanvas *canvas, SkPaint *painter) {
    dispatchChainFunction(DrawEventChain, this, canvas, painter);

    for (auto &child: children) {
        child->dispatchDrawEvent(canvas, painter);
    }
    return this;
};


/// Set Paints ///
template<typename RemoveEventCallBack>
Element *Element::addSetPaintsEvent(SetPaintsEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(SetPaintsEventChain, callBack, removeEventCallBack, SetPaintsEventChain == nullptr, true);
    return this;
};

Element *Element::dispatchSetPaintsEvent() {
    dispatchChainFunction(SetPaintsEventChain, this);
    return this;
};

/// Resize ///
template<typename RemoveEventCallBack>
Element *Element::addResizeEvent(ResizeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(ResizeEventChain, callBack, removeEventCallBack, ResizeEventChain == nullptr, true);
    return this;
};

Element *Element::dispatchResizeEvent(float width, float height) {
    dispatchChainFunction(ResizeEventChain, this, width, height);

    for (auto &child: children) {
        child->dispatchResizeEvent(width, height);
    }
    return this;
};


/// ADD CHILD
template<typename RemoveEventCallBack>
Element *Element::addAddChildEvent(AddChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {

    addChainFunction(AddChildEventChain, callBack, removeEventCallBack, AddChildEventChain == nullptr, true);
    return this;
};

Element *Element::dispatchAddChildEvent(Element *newChild) {
    dispatchChainFunction(AddChildEventChain, this, newChild);
    return this;
};

/// REMOVE CHILD
template<typename RemoveEventCallBack>
Element *Element::addRemoveChildEvent(RemoveChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(RemoveChildEventChain, callBack, removeEventCallBack, RemoveChildEventChain == nullptr, true);
    return this;
};

Element *Element::dispatchRemoveChildEvent(int removeIndex, int count) {
    dispatchChainFunction(RemoveChildEventChain, this, removeIndex, count);
    return this;
};


/// REPLACE CHILD
template<typename RemoveEventCallBack>
Element *Element::addReplaceChildEvent(ReplaceChildEventType &&callBack, RemoveEventCallBack &&removeEventCallBack) {
    addChainFunction(ReplaceChildEventChain, callBack, removeEventCallBack, ReplaceChildEventChain == nullptr, true);
    return this;
};

Element *Element::dispatchReplaceChildEvent(int replaceIndex, Element *oldChild, Element *newChild) {
    dispatchChainFunction(ReplaceChildEventChain, this, replaceIndex, oldChild, newChild);
    return this;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
