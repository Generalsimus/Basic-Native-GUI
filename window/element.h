//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_ELEMENT_H
#define CUDA_NEU_ELEMENT_H

#include "window.h"
#include "../../../../../Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/include/functional"
#include "../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/um/Windows.h"
#include "../../../../../Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/include/string"
#include "../../../../../Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/ucrt/stddef.h"


class Element;

class Window;

using DrawChainType = std::function<void(Element *, Window *)>;

class Element : public Event {
protected:

    int x;
    int y;
    int width;
    int height;


public:
    Element *parent;
    Element *children;
    int childCount;
 //   Window *window;

    Element *addDrawStyles(DrawChainType callBackStyleChain);


    Element *addChildElement();

    template<typename... Chi>
    Element *addChildElement(Element *child, Chi... rest);


    Element();

    template<typename... Args>
    explicit Element(Element *first, Args... rest);


    void drawMe() {
        return;
    }
};


#endif //CUDA_NEU_ELEMENT_H
