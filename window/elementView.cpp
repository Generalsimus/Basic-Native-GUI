//
// Created by PC on 9/3/2023.
//

#include "elementView.h"
#include "./utils.cpp"
#include "./events.cpp"


void ElementView::replaceChild(int replaceAtIndex, ElementView *newChild) {
    if (replaceAtIndex >= 0 && replaceAtIndex < children.size()) {
        auto oldValue = children[replaceAtIndex];
        children[replaceAtIndex] = newChild;
        this->dispatchReplaceChildEvent(replaceAtIndex, oldValue, newChild);
        oldValue->dispatchUnmountOnThreeEvent(this);
    } else {
        std::cout << "Invalid index." << std::endl;
    }
}

void ElementView::removeChild(int startIndex, int removeCount) {
    int endIndex = startIndex + removeCount;
    // Check if the indices are valid
    if (startIndex >= 0 && endIndex >= startIndex && endIndex < children.size()) {
        std::vector<ElementView *> removedElements;

        for (int i = startIndex; i < endIndex; i++) {
            removedElements.push_back(children[i]);
        };
        // Calculate iterators for the elements to remove
        auto firstToRemove = children.begin() + startIndex;
        auto lastToRemove = children.begin() + endIndex + 1; // Add 1 to include the element at endIndex

        // Erase the elements between startIndex and endIndex
        children.erase(firstToRemove, lastToRemove);
        for (ElementView *element: removedElements) {
            element->dispatchUnmountOnThreeEvent(this);
        }
    } else {
        // Handle the case where the indices are invalid
        std::cout << "Invalid indices." << std::endl;
    }
    this->dispatchRemoveChildEvent(startIndex, removeCount);
}

ElementView *ElementView::addChild() {
    return this;
};

template<typename... Chi>
ElementView *ElementView::addChild(ElementView *child, Chi... rest) {
    // printf("RUN addChild\n");
    child->parent = this;
    child->window = this->window;

    this->children.push_back(child);

    this->dispatchAddChildEvent(child);
    child->dispatchMountOnThreeEvent(this);

    return this->addChild(rest...);
};

ElementView::ElementView() {
    // printf("RUN Element() NO CHILD\n");
    this->InitCustomEventListeners();
    this->resetContainFn();
};


void ElementView::InitCustomEventListeners() {
    int downTypeNum = -1;
    auto self = this;
    this->addTouchDownEvent([&downTypeNum](ElementView *element, int windowX, int windowY, int typeIndex) {
        downTypeNum = typeIndex;
    });
    this->addTouchUpEvent([&downTypeNum, self](ElementView *element, int windowX, int windowY, int typeIndex) {
        if (downTypeNum == typeIndex) {
            self->dispatchTouchEvent(windowX, windowY, typeIndex);
            downTypeNum = -1;
        };
    });


    this->addResizeEvent([](ElementView *element, float newWidth, float newHeight) mutable {
        element->width = newWidth;
        element->height = newHeight;

    });

}


template<typename CallBackFunc>
void ElementView::callSafeOnMountThree(CallBackFunc callback) {
    if (this->window == nullptr || this->parent == nullptr) {
        callback(this, this->parent, this->window);
    } else {
        std::function < void() > removeMounterEvent = []() {

        };
        this->addMountOnThreeEvent(
                [callback, removeMounterEvent](ElementView *element, ElementView *parentElement) mutable {
                    callback(element, element->parent, element->window);
                    removeMounterEvent();
                }, removeMounterEvent);
    }
}


template<typename... Args>
ElementView::ElementView(ElementView *first, Args... rest) {
    ///  printf("RUN Element() WITH CHILD\n");


    addChild(first);
    addChild(rest...);
}

template<typename PaintFunction, typename... Args>
ElementView *ElementView::setPaints(PaintFunction paintCallback, Args... args) {
    this->resetContainFn();
    auto awaitAsyncGroup = CreateAsyncAwaitGroup();
    SetEachPainters(std::forward<PaintFunction>(paintCallback), std::forward<Args>(args)...);

    awaitAsyncGroup();

    auto awaitAsyncGroup2 = CreateAsyncAwaitGroup();
    dispatchSetPaintsEvent();
    awaitAsyncGroup2();

//    if (this->parent == nullptr) {
//        std::function<void()> removeMounter = []() {
//
//        };
//
//        this->addMountOnThreeEvent([removeMounter](ElementView *element, ElementView *parent) mutable {
//            element->dispatchDrawEvent();
//            removeMounter();
//        }, removeMounter);
//    } else {
//        this->dispatchDrawEvent();
//    }

    return this;
};
void ElementView::SetEachPainters() {

}

template<typename PaintFunction, typename... Args>
void ElementView::SetEachPainters(PaintFunction paintCallback, Args... args) {
    paintCallback(this);
    SetEachPainters(args...);
};

template<typename CallBackFunction, typename RemoveChainFunction>
void ElementView::addChainFunction(CallBackFunction &chainFunc, CallBackFunction &callBack,
                                   RemoveChainFunction &removeChainFunction,
                                   bool startFromNewPoint,
                                   bool callAsync) {

//    if(){
//
//    }else {
//
//    }
    //  printf("\nRUN addChainFunction() %d\n", startFromNewPoint);


//    CallBackFunction &&currentConnector = nullptr;
//    CallBackFunction *currentConnector = new CallBackFunction;
////    std::shared_ptr<CallBackFunction> currentConnector = std::make_shared<CallBackFunction>([](){});
//
//
//
//    auto self = this;
//    auto currentCallBack = std::move(callBack);
//
//    if (startFromNewPoint) {
//        if (callAsync) {
//            *currentConnector = [currentCallBack, self]<typename... Args>(Args &&... args) {
//                runAsyncTask(currentCallBack, std::forward<Args>(args)...);
//            };
//        } else {
//            *currentConnector = currentCallBack;
//        }
//
//        if (removeChainFunction != nullptr) {
//            RemoveChainFunction currentRemoveChainFunction = std::move(removeChainFunction);
//            removeChainFunction = [currentRemoveChainFunction, &currentConnector]<typename... Args>(Args &&... args) {
//                //   printf("REMOVE");
////                *currentConnector = nullptr;
//                return currentRemoveChainFunction(std::forward<Args>(args)...);
//            };
//        };
//
//
//        chainFunc = [currentConnector]<typename... Args>(Args &&... args) {
//            if (*currentConnector != nullptr) {
//                (*currentConnector)(std::forward<Args>(args)...);
//            }
//        };
//    } else {
//        auto currentChainFunc = std::move(chainFunc);
//
//        if (callAsync) {
//            *currentConnector = [currentCallBack, currentChainFunc, self]<typename... Args>(Args &&... args) {
//                currentChainFunc(std::forward<Args>(args)...);
//
//                runAsyncTask(currentCallBack, std::forward<Args>(args)...);
//            };
//        } else {
//            *currentConnector = [currentCallBack, currentChainFunc, &self]<typename... Args>(Args &&... args) {
//                currentChainFunc(std::forward<Args>(args)...);
//                currentCallBack(std::forward<Args>(args)...);
//            };
//        }
//
//        if (removeChainFunction != nullptr) {
//            RemoveChainFunction currentRemoveChainFunction = std::move(removeChainFunction);
//            removeChainFunction = [currentRemoveChainFunction, currentChainFunc, currentConnector]<typename... Args>(
//                    Args &&... args) {
//                *currentConnector = currentChainFunc;
//                return currentRemoveChainFunction(std::forward<Args>(args)...);
//            };
//        };
//
//        chainFunc = [currentConnector]<typename... Args>(Args &&... args) {
//            (*currentConnector)(std::forward<Args>(args)...);
//        };
//    };


};


template<class ChainFunc, class... Args>
void ElementView::dispatchChainFunction(ChainFunc &chainFunc, Args &&... args) {
//    printf("RUN dispatchChainFunction()\n");

    if (chainFunc != nullptr) {
        chainFunc(std::forward<Args>(args)...);
    }

}


/// START Coordinates Contain Check //
ElementView *ElementView::resetContainFn() {
    this->contains = [this](float x, float y) {
        return (
                (x > this->x) &&
                (x < (this->x + this->width)) &&
                (y > this->y) &&
                (y < (this->y + this->height))
        );
    };
    return this;
}

template<class CallBackCheck>
ElementView *ElementView::addContainsFn(CallBackCheck &&callBack) {
    auto currentContains = this->contains;
    this->contains = [currentContains, callBack](float x, float y) mutable {
        return (currentContains(x, y) && callBack(x, y));
    };
    return this;
}
/// END Coordinates Contain Check //