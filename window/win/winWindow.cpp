//
// Created by PC on 9/3/2023.
//

#include "winWindow.h"
#include "../window.cpp"
#include <windows.h>
#include "utils.cpp"

winWindow::winWindow(const std::string &title, int width, int height): Window(title, width, height) {
    printf("RUN winWindow");
    this->width = width;
    this->height = height;

    // Register window class
    WNDCLASS wc = CreateWNDCLASS(title);


    // Create window
    HWND hwnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width,
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