//
// Created by PC on 9/3/2023.
//

#include "element.h"
#include "./utils.cpp"
#include "./events.cpp"
#include "./asyncTaskController.cpp"

Element *Element::addChildElement() {
    return this;
};

template<typename... Chi>
Element *Element::addChildElement(Element *child, Chi... rest) {
    printf("RUN addChildElement\n");


    this->children.push_back(child);

    child->parent = this;


    return this->addChildElement(rest...);
};

Element::Element() : x(0), y(0) {
    printf("RUN Element() NO CHILD\n");
    this->InitCustomEventListeners();
};

void Element::InitCustomEventListeners() {
    int downTypeNum = -1;
    auto self = this;
    this->addTouchDownEvent([&downTypeNum](Element *element, int windowX, int windowY, int typeIndex) {
        downTypeNum = typeIndex;
    });
    this->addTouchUpEvent([&downTypeNum, self](Element *element, int windowX, int windowY, int typeIndex) {
        if (downTypeNum == typeIndex) {
            self->dispatchTouchEvent(windowX, windowY, typeIndex);
            downTypeNum = -1;
        };
    });


    this->addTouchMoveEvent([self](Element *element, int windowX, int windowY) {
        self->dispatchTouchOverEvent();
    });

}

template<typename... Args>
Element::Element(Element *first, Args... rest):x(0), y(0) {
    printf("RUN Element() WITH CHILD\n");


    addChildElement(first);
    addChildElement(rest...);
}


template<typename CallBackFunction, typename RemoveChainFunction>
void Element::addChainFunction(CallBackFunction &chainFunc, CallBackFunction &callBack,
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
void Element::dispatchChainFunction(ChainFunc &chainFunc, Args &&... args) {
//    printf("RUN dispatchChainFunction()\n");

    if (chainFunc != nullptr) {
        chainFunc(std::forward<Args>(args)...);
    }

}


bool Element::PositionIsOver(int windowX, int windowY) {
    return ((windowX > this->x) && (windowX < (this->x + this->width)) && (windowY > this->y) &&
            (windowY < (this->y + this->height)));
}

void Element::SetEachPainters() {

};
template<typename PaintFunction, typename... Args>
void Element::SetEachPainters(PaintFunction paintCallback, Args... args) {
    paintCallback(this);
};