//
// Created by PC on 9/3/2023.
//

#include "elementView.h"
#include "./utils.cpp"
#include "./events.cpp"
#include "./asyncTaskController.cpp"

void ElementView::replaceChild(int replaceAtIndex, ElementView *newChild) {
    if (replaceAtIndex >= 0 && replaceAtIndex < children.size()) {
        auto oldValue = children[replaceAtIndex];
        children[replaceAtIndex] = newChild;
        this->dispatchReplaceChildEvent(replaceAtIndex, oldValue, newChild);
    } else {
        std::cout << "Invalid index." << std::endl;
    }
}

void ElementView::removeChild(int startIndex, int removeCount) {
    int endIndex = startIndex + removeCount;
    // Check if the indices are valid
    if (startIndex >= 0 && endIndex >= startIndex && endIndex < children.size()) {
        // Calculate iterators for the elements to remove
        auto firstToRemove = children.begin() + startIndex;
        auto lastToRemove = children.begin() + endIndex + 1; // Add 1 to include the element at endIndex

        // Erase the elements between startIndex and endIndex
        children.erase(firstToRemove, lastToRemove);
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
    printf("RUN addChild\n");

    this->children.push_back(child);

    this->dispatchAddChildEvent(child);

    return this->addChild(rest...);
};

ElementView::ElementView() : x(0), y(0) {
    printf("RUN Element() NO CHILD\n");
    this->InitCustomEventListeners();
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


    this->addTouchMoveEvent([self](ElementView *element, int windowX, int windowY) {
        self->dispatchTouchOverEvent();
    });

}


template<typename... Args>
ElementView::ElementView(ElementView *first, Args... rest):x(0), y(0) {
    printf("RUN Element() WITH CHILD\n");


    addChild(first);
    addChild(rest...);
}


template<typename CallBackFunction, typename RemoveChainFunction>
void ElementView::addChainFunction(CallBackFunction &chainFunc, CallBackFunction &callBack,
                               RemoveChainFunction &removeChainFunction,
                               bool startFromNewPoint,
                               bool callAsync) {
    printf("\nRUN addChainFunction() %d\n", startFromNewPoint);


//    CallBackFunction &&currentConnector = nullptr;
    CallBackFunction *currentConnector = new CallBackFunction;
//    *dynamicInt = originalInt;


    auto self = this;
    auto currentCallBack = std::move(callBack);

    if (startFromNewPoint) {
        if (callAsync) {
            *currentConnector = [currentCallBack, self]<typename... Args>(Args &&... args) {
                self->addAsyncTask(currentCallBack, std::forward<Args>(args)...);
            };
        } else {
            *currentConnector = currentCallBack;
        }

        if (removeChainFunction != nullptr) {
            RemoveChainFunction currentRemoveChainFunction = std::move(removeChainFunction);
            removeChainFunction = [currentRemoveChainFunction, &currentConnector]<typename... Args>(Args &&... args) {
                printf("REMOVE");
                *currentConnector = nullptr;
                return currentRemoveChainFunction(std::forward<Args>(args)...);
            };
        };


        chainFunc = [currentConnector]<typename... Args>(Args &&... args) {
            if (*currentConnector != nullptr) {
                (*currentConnector)(std::forward<Args>(args)...);
            }
        };
    } else {
        auto currentChainFunc = std::move(chainFunc);

        if (callAsync) {
            *currentConnector = [currentCallBack, currentChainFunc, self]<typename... Args>(Args &&... args) {
                currentChainFunc(std::forward<Args>(args)...);

                self->addAsyncTask(currentCallBack, std::forward<Args>(args)...);
            };
        } else {
            *currentConnector = [currentCallBack, currentChainFunc, &self]<typename... Args>(Args &&... args) {
                currentChainFunc(std::forward<Args>(args)...);
                currentCallBack(std::forward<Args>(args)...);
            };
        }

        if (removeChainFunction != nullptr) {
            RemoveChainFunction currentRemoveChainFunction = std::move(removeChainFunction);
            removeChainFunction = [currentRemoveChainFunction, currentChainFunc, currentConnector]<typename... Args>(
                    Args &&... args) {
                *currentConnector = currentChainFunc;
                return currentRemoveChainFunction(std::forward<Args>(args)...);
            };
        };

        chainFunc = [currentConnector]<typename... Args>(Args &&... args) {
            (*currentConnector)(std::forward<Args>(args)...);
        };
    };


};


template<class ChainFunc, class... Args>
void ElementView::dispatchChainFunction(ChainFunc &chainFunc, Args &&... args) {
//    printf("RUN dispatchChainFunction()\n");

    if (chainFunc != nullptr) {
        chainFunc(std::forward<Args>(args)...);
    }

}


bool ElementView::PositionIsOver(int windowX, int windowY) {
    return ((windowX > this->x) && (windowX < (this->x + this->width)) && (windowY > this->y) &&
            (windowY < (this->y + this->height)));
}

void ElementView::SetEachPainters() {

};

template<typename PaintFunction, typename... Args>
void ElementView::SetEachPainters(PaintFunction paintCallback, Args... args) {
    paintCallback(this);
};