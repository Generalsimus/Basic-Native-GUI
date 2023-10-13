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

//class Cursor{
//
//};


class winWindow : public Window {
public:
//    const void *pixelsAddr;
    BITMAPINFO bmi;


    winWindow(const std::string &title, float windowWidth, float WindowHeight);

    HWND hwnd;


    std::function<void()> setCursorInsiderFunc = []() {
        SetCursor(LoadCursor(nullptr, IDC_ARROW));
//        ShowCursor(FALSE);
    };

    std::function<void()> setCursor(ElementView *cursorElement);
    std::function<void()> setCursor(Cursor cursor);

//    void SetCursor() {
//
//    }
//    SetCursor(ElementView* customcursor){
//
//    };


//    void WinSetDIBitsToDevice(HDC hdc,float width,float height);
//    void refreshFrame() const;

};


#endif //CUDA_NEU_WINWINDOW_H
