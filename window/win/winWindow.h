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
//#include <string>
//#include <cstddef>
//#include <cstdlib>

//class Cursor{
//
//};


class winWindow : public Window {
public:
//    const void *pixelsAddr;
    BITMAPINFO bmi;


    winWindow(const std::string &title, float windowWidth, float WindowHeight);

    HWND hwnd;

    HCURSOR currentWinCursor = LoadCursor(nullptr, IDC_ARROW);


    Cursor cursor = Cursor::Arrow;
    std::function<void()> setCursor(ElementView *cursorElement);

    std::function<void()> setCursor(Cursor cursor);

    void refreshFrame() override;


};


#endif //CUDA_NEU_WINWINDOW_H
