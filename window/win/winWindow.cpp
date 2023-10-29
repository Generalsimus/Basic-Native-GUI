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

};

std::function<void()> winWindow::setCursor(ElementView *cursor) {
    auto UndoSetCursor = this->setCursorInsiderFunc;
    return UndoSetCursor;
}

std::function<void()> winWindow::setCursor(Cursor cursor) {
    printf("setCursor %d\n", cursor);
    auto UndoSetCursor = this->setCursorInsiderFunc;
    switch (cursor) {
        case Cursor::Arrow:
            this->setCursorInsiderFunc = []() {
                SetCursor(LoadCursor(nullptr, IDC_ARROW));
            };
            break;
        case Cursor::Text:
            this->setCursorInsiderFunc = []() {
                SetCursor(LoadCursor(nullptr, IDC_IBEAM));
            };
            break;
        case Cursor::Wait:
            this->setCursorInsiderFunc = []() {
                SetCursor(LoadCursor(nullptr, IDC_WAIT));
            };
            break;
        case Cursor::None:
            this->setCursorInsiderFunc = []() {
                ShowCursor(FALSE);
            };
            break;

    }
    this->setCursorInsiderFunc();
    return UndoSetCursor;
}

void winWindow::refreshFrame() {
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(this->hwnd, &ps);

    SetDIBitsToDevice(hdc, 0, 0, this->width, this->height, 0, 0, 0, this->height, this->pixels.addr(),
                      &this->bmi, DIB_RGB_COLORS);
    // Clean up
    EndPaint(hwnd, &ps);
};