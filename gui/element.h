//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_ELEMENT_H
#define CUDA_NEU_ELEMENT_H

#include "../window/window.h"
#include <functional>
#include <windows.h>
#include <string>
#include <stddef.h>

class Element;

using DrawChainType = std::function<void(Element *)>;

class Element {
private:
    int x;
    int y;
    int width;
    int height;
    // using EventCallback = std::function<void()>;
    Element *children;
    int childCount;
    std::optional<Window> window;
    Element *parent;
    DrawChainType drawChain;


public:
    Element *addDrawStyles(DrawChainType callBackStyleChain);

    Element *addChildElement(Element *child);

    Element(Element const &first);
    Element();
    template<typename... Args>
    explicit Element(Element first, Args... rest);


};


#endif //CUDA_NEU_ELEMENT_H
