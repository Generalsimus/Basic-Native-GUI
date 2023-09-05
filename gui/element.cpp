//
// Created by PC on 9/3/2023.
//

#include "element.h"
#include "utils.cpp"



Element* Element::addChildElement(Element *child) {

    /*this->children = AddArrayElement(this->children, this->childCount, *child);

    this->childCount++;
    child->parent = this;
    child->window = this->window;
    this->window.refreshFrame();*/
   /* this->childCount++;
    child->parent = this;
    child->window = this->window;
    this->window.refreshFrame();*/
    return this;
};

Element* Element::addDrawStyles(DrawChainType callBackStyleChain) {
//   // DrawChainType currentChain = this->drawChain;
//
//    /*this->drawChain = []() {
//
//    };*/
    return this;
};


Element::Element() {
    printf("RUN Element2222\n");

};

template<typename... Args>
Element::Element(Element first, Args... rest) {
    printf("RUN Element1111\n");

};

Element::Element(Element const &first) {
    printf("RUN firstfirstfirstfirstfirstfirst\n");

}
