//
// Created by PC on 9/3/2023..

//

#include "winWindow.h"
#include "../window.cpp"
#include <windows.h>
#include "utils.cpp"


winWindow::winWindow(const std::string &title, float windowWidth, float windowHeight) : Window(title, windowWidth,
                                                                                               windowHeight) {
    // printf("\nRUN winWindow\n");

    ///////////////////////////
    this->width = windowWidth;
    this->height = windowHeight;
    auto self = this;

    this->bmi = CreateBitmapInfo(static_cast<int>(windowWidth), static_cast<int>(windowHeight));

    this->addResizeEvent([self](ElementView *element, float elementWidth, float elementHeight) {
        self->bmi.bmiHeader.biWidth = static_cast<int>(elementWidth);
        self->bmi.bmiHeader.biHeight = -static_cast<int>(elementHeight);
    });

    runAsyncTask(CreateWindowsWindows, title, windowWidth, windowHeight, this);

    while (this->surface == nullptr) {

    };
//    auto self = this;
//    this->addTouchMoveEvent([self](ElementView *element, float x, float y){
//        self->setCursorInsiderFunc();
//    });

};

std::function<void()> winWindow::setCursor(ElementView *newCursor) {
    return std::function([]() {

    });
}

std::function<void()> winWindow::setCursor(Cursor newCursor) {
    auto previousCursor = this->cursor;
    auto self = this;

    if (previousCursor == Cursor::None && newCursor != Cursor::None) {
        ShowCursor(TRUE);
    }
    this->cursor = newCursor;
    SendMessage(self->hwnd, WM_SETCURSOR, 0, 0);

    return std::function([previousCursor, self]() mutable {
        self->cursor = previousCursor;
        SendMessage(self->hwnd, WM_SETCURSOR, 0, 0);
    });
}

void winWindow::refreshFrame() {
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(this->hwnd, &ps);

    SetDIBitsToDevice(hdc, 0, 0, this->width, this->height, 0, 0, 0, this->height, this->pixels.addr(),
                      &this->bmi, DIB_RGB_COLORS);

    EndPaint(hwnd, &ps);
};