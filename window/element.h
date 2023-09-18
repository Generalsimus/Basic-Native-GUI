//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_ELEMENT_H
#define CUDA_NEU_ELEMENT_H

#include "functional"
#include "Windows.h"
#include "string"
#include <cstddef>
#include <vector>
#include <future>
#include <map>
#include <any>

template<typename... Args>
using EEEEEEEE = std::function<void(Args &&...)>;

class Element;

using TouchEventType = std::function<void(Element *, int, int)>;

class Element {
public:

    int x;
    int y;
    int width;
    int height;


    Element *parent;
    std::vector<Element *> children;


    Element *addDrawStyles();


    Element *addChildElement();

    template<typename... Chi>
    Element *addChildElement(Element *child, Chi... rest);


    Element();

    template<typename... Args>
    explicit Element(Element *first, Args... rest);

    // EVENTS START
    Element *addTouchEvent();

    template<typename... Args>
    Element *addTouchEvent(TouchEventType firstCallBack, Args... rest);

    void dispatchTouchEvent(int x, int y);
    // EVENTS END

    template<class Func, typename... Args>
    void addAsyncTask(Func &&func, Args... args);

    void awaitAll();


    template<typename CallBackFunc>
    Element *addEvent(const std::string &name, const CallBackFunc &callBack, bool callAsync = true);


    template<typename... Args>
    Element *dispatchEvent(const std::string &name, Args &&... args);

private:


    // EVENTS MaP START
    std::map<std::string, std::any> events;
    // EVENTS MaP END
    std::vector<std::future<void>> tasks_;
    std::mutex mutex_;


protected:

    template<typename CallBackFunction>
    void addChainFunction(CallBackFunction &chainFunc, CallBackFunction callBack, bool startFromNewPoint = false,
                          bool callAsync = true);

    template<typename ChainFunc, typename... Args>
    void dispatchChainFunction(ChainFunc &chainFunc, Args &&... args);


    void drawMe() {
        return;
    }
};


#endif //CUDA_NEU_ELEMENT_H
