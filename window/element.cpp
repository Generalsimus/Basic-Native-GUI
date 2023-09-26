//
// Created by PC on 9/3/2023.
//

#include "element.h"
#include "./utils.cpp"
#include "./events.cpp"

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


    this->addTouchMovieEvent([self](Element *element, int windowX, int windowY) {
        self->dispatchTouchOverEvent();
    });

}

template<typename... Args>
Element::Element(Element *first, Args... rest):x(0), y(0) {
    printf("RUN Element() WITH CHILD\n");
    addChildElement(first);
    addChildElement(rest...);
}


template<typename CallBackFunction>
void Element::addChainFunction(CallBackFunction &chainFunc, CallBackFunction &callBack, bool startFromNewPoint,
                               bool callAsync) {
    printf("\nRUN addChainFunction() %d\n", startFromNewPoint);


    auto self = this;
    auto currentCallBack = std::move(callBack);

    if (startFromNewPoint) {
        if (callAsync) {
            chainFunc = [currentCallBack, self]<typename... Args>(Args &&... args) {
                self->addAsyncTask(currentCallBack, std::forward<Args>(args)...);
            };
        } else {
            chainFunc = currentCallBack;
        }
    } else {
        auto currentChainFunc = std::move(chainFunc);

        if (callAsync) {
            chainFunc = [currentCallBack, currentChainFunc, self]<typename... Args>(Args &&... args) {
                currentChainFunc(std::forward<Args>(args)...);

                self->addAsyncTask(currentCallBack, std::forward<Args>(args)...);
            };
        } else {
            chainFunc = [currentCallBack, currentChainFunc, &self]<typename... Args>(Args &&... args) {
                currentChainFunc(std::forward<Args>(args)...);
                currentCallBack(std::forward<Args>(args)...);
            };
        }
    };


}


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
