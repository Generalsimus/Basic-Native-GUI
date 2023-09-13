//
// Created by PC on 9/3/2023.
//

#include "element.h"
#include "./utils.cpp"
#include "../../../../../Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/include/cstddef"
#include "../../../../../Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/include/iostream"

Element *Element::addChildElement() {
    return this;
};

template<typename... Chi>
Element *Element::addChildElement(Element *child, Chi... rest) {

    printf("RUN addChildElement\n");

    this->children = AddArrayElement(this->children, this->childCount, *child);


    this->childCount++;
    child->parent = this;
//    child->window = this->window;

//    if (this->window != nullptr) {
//        this->window->refreshFrame();
//    }

    return this->addChildElement(rest...);
};

Element *Element::addDrawStyles(DrawChainType callBackStyleChain) {
    /* DrawChainType currentChain = this->drawChain;

       this->drawChain = [currentChain, callBackStyleChain](Element * el, Window* win) {
           currentChain(el, win);
           callBackStyleChain(el, win);
       };*/

    return this;
}

Element::Element() : children(new Element[0]), childCount(0) {
    printf("RUN Element() NO CHILD\n");

};

template<typename... Args>
Element::Element(Element *first, Args... rest):children(new Element[0]), childCount(0) {
    printf("RUN Element() WITH CHILD\n");

    addChildElement(first);
    addChildElement(rest...);
};