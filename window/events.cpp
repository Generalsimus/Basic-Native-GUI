
/// EVENTS LIST ////////////////////////////////////////////////////////////////////////////////////////

/// TOUCH OVER //
Element *Element::addTouchOverEvent(TouchOverEventType &&callBack) {
    printf("RUN addTouchOverEvent()");

    addChainFunction(TouchOverEventChain, callBack, TouchOverEventChain == nullptr, true);

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
Element *Element::addTouchLeaveEvent(TouchLeaveEventType &&callBack) {
    printf("RUN addTouchOverEvent()");

    addChainFunction(TouchLeaveEventChain, callBack, TouchLeaveEventChain == nullptr, true);


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
Element *Element::addTouchMovieEvent(TouchMoveEventType &&firstCallBack) {
    printf("RUN addTouchDownEvent()");

    addChainFunction(TouchMoveEventChain, firstCallBack, TouchMoveEventChain == nullptr, true);

    return this;
}


Element *Element::dispatchTouchMovieEvent(int windowX, int windowY, bool isAsync, bool useTouchOverChild) {
//    printf("RUN dispatchTouchDownEvent() X:%d, Y: %d \n", windowX, windowY);

    if (PositionIsOver(windowX, windowY)) {
        dispatchChainFunction(TouchMoveEventChain, this, windowX, windowY);

        for (auto &child: children) {
            child->dispatchTouchMovieEvent(windowX, windowY);
        }
    }
    return this;
};


/// TOUCH DOWN //
Element *Element::addTouchDownEvent(TouchDownEventType &&firstCallBack) {
    printf("RUN addTouchDownEvent()");

    addChainFunction(TouchDownEventChain, firstCallBack, TouchDownEventChain == nullptr, true);

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
Element *Element::addTouchUpEvent(TouchUpEventType &&firstCallBack) {
    printf("RUN addTouchUpEvent()");

    addChainFunction(TouchUpEventChain, firstCallBack, TouchUpEventChain == nullptr, true);

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
Element *Element::addTouchEvent(TouchEventType &&firstCallBack) {
    printf("RUN addTouchUpEvent()");

    addChainFunction(TouchEventChain, firstCallBack, TouchEventChain == nullptr, true);

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
Element *Element::addKeyDownEvent(KeyDownEventType &&callBack) {
    printf("RUN addKeyDownEvent()");

    addChainFunction(KeyDownEventChain, callBack, KeyDownEventChain == nullptr, true);
    return this;
}

Element *Element::dispatchKeyDownEvent(int keyIndex) {

    dispatchChainFunction(KeyDownEventChain, this, keyIndex);

    return this;
};

/// KEY Up //
Element *Element::addKeyUpEvent(KeyUpEventType &&callBack) {
    printf("RUN addKeyDownEvent()");

    addChainFunction(KeyUpEventChain, callBack, KeyUpEventChain == nullptr, true);
    return this;
}

Element *Element::dispatchKeyUpEvent(int keyIndex) {

    dispatchChainFunction(KeyUpEventChain, this, keyIndex);

    return this;
};


/// KEY ///
Element *Element::addKeyEvent(KeyEventType &&callBack) {
    printf("RUN addKeyDownEvent()");

    addChainFunction(KeyEventChain, callBack, KeyEventChain == nullptr, true);
    return this;
}

Element *Element::dispatchKeyEvent(int keyIndex) {

    dispatchChainFunction(KeyEventChain, this, keyIndex);

    return this;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
