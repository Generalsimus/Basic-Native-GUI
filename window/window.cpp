//
// Created by PC on 8/31/2023.
//
#include "window.h"
#include <windows.h>
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include <string>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.cpp"

void draw(SkCanvas *canvas) {
    canvas->save();
    canvas->translate(SkIntToScalar(128), SkIntToScalar(128));
    canvas->rotate(SkIntToScalar(45));
    SkRect rect = SkRect::MakeXYWH(-90.5f, -90.5f, 181.0f, 181.0f);
    SkPaint paint;
    paint.setColor(SK_ColorBLUE);
    canvas->drawRect(rect, paint);
    canvas->restore();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    Window *window = (Window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);


    switch (msg) {
        case WM_PAINT: {
            printf("WM_PAINT\n");
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetWindowRect(hwnd, &rect);

            window->width = rect.right - rect.left;
            window->height = rect.bottom - rect.top;


//            window->surface = window->surface->makeSurface(window->width, window->height);

            /*SkCanvas *canvas = window->surface->getCanvas();*/
/*
            draw(canvas);




            SkBitmap bitmap;
            bitmap.allocPixels(window->surface->imageInfo());


            draw(canvas);*/

            SkBitmap skBitmap;
            skBitmap.allocN32Pixels(800, 600);  // Width and height of the bitmap
            SkCanvas canvas(skBitmap);

            // Draw something on the SkCanvas (for example, a red rectangle)
            SkPaint paint;
            paint.setColor(SK_ColorRED);
            canvas.drawRect(SkRect::MakeXYWH(100, 100, 200, 200), paint);
            /* BITMAPINFO bmi = CreateBitmapInfo(&bitmap);*/
            const void *pixels = skBitmap.getPixels();


            BITMAPINFO bmi = CreateBitmapInfo(&skBitmap);


            SetDIBitsToDevice(hdc, 0, 0, skBitmap.width(), skBitmap.height(),
                              0, 0, 0, skBitmap.height(), pixels, &bmi, DIB_RGB_COLORS);

            // Release the HDC
            //  ReleaseDC(NULL, hdc);
            /*  SetDIBitsToDevice(hdc, 0, 0, window->width, window->height, 0, 0, 0, window->height , bitmap.getPixels(),
                                &bmi, DIB_RGB_COLORS);
  */


            // Clean up
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CLOSE:
            printf("WM_CLOSE\n");
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            printf("WM_DESTROY\n");

            PostQuitMessage(0);
            return 0;
        default:
            //printf("Received message: 0x%X\n", msg);

            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
};

Window::Window(const std::string &title, int width, int height): width(width), height(height) {

    // Register window class
    WNDCLASS wc = CreateWNDCLASS(title, WndProc);


    // Create window
    hwnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width,
                             height, NULL, NULL, wc.hInstance, NULL);

    if (!hwnd) {
        printf("CreateWindow() ERROR\n");
        return;
    }





    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) this);
    RegisterTouchWindow(hwnd, 0);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

};