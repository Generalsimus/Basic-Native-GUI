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
class Window;

using DrawChainType = std::function<void(Element *, Window*)>;

class Element {
private:

    int x;
    int y;
    int width;
    int height;



    DrawChainType drawChain;


public:
    Element *parent;
    Element *children;
    int childCount;
    Window *window;

    Element *addDrawStyles(DrawChainType callBackStyleChain);



    Element *addChildElement();
    template<typename... Chi>
    Element *addChildElement(Element *child, Chi... rest);



    Element();
    template<typename... Args>
    explicit Element(Element* first, Args... rest);


    void drawMe(){
        return ;
    }
};


#endif //CUDA_NEU_ELEMENT_H
