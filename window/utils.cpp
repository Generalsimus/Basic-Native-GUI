//
// Created by PC on 8/31/2023.
//

#include <windows.h>
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"

BITMAPINFO CreateBitmapInfo(SkBitmap *bitmap) {
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bitmap->width();
    bmi.bmiHeader.biHeight = -bitmap->height(); // top-down image
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;

    return bmi;
};

typedef LRESULT CALLBACK WndProcDef(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDCLASS CreateWNDCLASS(const std::string &title, WndProcDef WndProc) {
    WNDCLASS wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;

    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH) (COLOR_BACKGROUND);
    wc.lpszClassName = title.c_str();
    if (!RegisterClass(&wc)) {
        printf("CreateWNDCLASS() ERROR\n");
    }
    return wc;
};
