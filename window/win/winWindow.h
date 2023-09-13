//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_WINWINDOW_H
#define CUDA_NEU_WINWINDOW_H

#include <windows.h>
#include "../window.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include <string>
#include <cstddef>
#include <cstdlib>

class winWindow : public Window {
public:
    const void *pixelsAddr;
    BITMAPINFO bmi;

    winWindow(const std::string &title, int width, int height);

    void refreshFrame() override;

    HWND hwnd;

    void WinSetDIBitsToDevice(HDC hdc);

private:

};


#endif //CUDA_NEU_WINWINDOW_H
