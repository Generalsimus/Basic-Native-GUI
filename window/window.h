//
// Created by PC on 8/31/2023.
//

#ifndef CUDA_NEU_WINDOW_H
#define CUDA_NEU_WINDOW_H

#include <windows.h>
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include <string>
#include <cstddef>
#include <cstdlib>
#include "element.h"


class Window : public Element {
private:

public:
    sk_sp<SkSurface> surface;
    int id;


    virtual void refreshFrame();

protected:
    Window(const std::string &title, int width, int height);
};


#endif //CUDA_NEU_WINDOW_H
