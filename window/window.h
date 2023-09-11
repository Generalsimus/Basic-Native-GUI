//
// Created by PC on 8/31/2023.
//

#ifndef CUDA_NEU_WINDOW_H
#define CUDA_NEU_WINDOW_H

#include <windows.h>
#include "./event.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include <string>
#include <cstddef>
#include <cstdlib>
#include "../gui/element.h"


class Window : public Event {
private:
//    MouseMoveFuncType mouseMoveCain;
public:
    sk_sp<SkSurface> surface;


    int id;

    int width;
    int height;

    Element *mainElement;

    void setMainElement(Element *element);

    virtual void refreshFrame();
    // decltype(CreateEventChain<OnPaintEventType>()) addOnPaintEvent;

protected:
    Window(const std::string &title, int width, int height);

};


#endif //CUDA_NEU_WINDOW_H
