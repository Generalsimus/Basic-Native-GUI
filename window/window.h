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
#include <stddef.h>

typedef bool (*MouseMoveFuncType)(int x, int y);

class Window {
private:
    MouseMoveFuncType mouseMoveCain;
public:
    Window(const std::string &title, int width, int height);

    int width;
    int height;

/*
    SkBitmap bitmap;
    SkCanvas canvas;
*/

   void refreshFrame();


};


#endif //CUDA_NEU_WINDOW_H
