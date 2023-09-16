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

    template<typename Func, typename... Args>
    void addAsyncTask(Func &&func, Args &&... args);

    void awaitAll();




//    std::map<std::string, std::vector<void (*)(int)> > events;

//    template <typename... Args>
//    using EventChainCallbackFunc = std::function<void(Args...)>;

    // Store event listeners with std::variant for different argument types
    std::map<std::string, std::any> events;



//    std::map<std::string,std::function<void(*)()>> events;

//    std::map<std::string, std::function<void()>> events;

//    std::function<void()> eventsChain;

//    template<typename CallBackFunc>
//    void addEvent(const std::string &name, CallBackFunc callBack);

    template<typename CallBackFunc>
    void addEvent(const std::string &name, CallBackFunc callBack);

    template<typename CallBackFunc, typename... Args>
    void dispatchEvent(const std::string &name, Args &&... args);

private:
    // EVENTS CHAIN START
    TouchEventType TouchEventChain = nullptr;
    // EVENTS CHAIN END
    std::vector<std::future<void>> tasks_;
    std::mutex mutex_;


protected:

    template<typename ChainFuncType>
    void addChainFunction(ChainFuncType &chainFunc, ChainFuncType callBack, bool callAsync = true);

    template<typename ChainFunc, typename... Args>
    void dispatchChainFunction(ChainFunc &chainFunc, Args &&... args);


    void drawMe() {
        return;
    }
};


#endif //CUDA_NEU_ELEMENT_H
