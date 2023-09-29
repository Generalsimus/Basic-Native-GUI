//
// Created by PC on 9/3/2023.
//

#include "winWindow.h"
#include "../window.cpp"
#include <windows.h>
#include "utils.cpp"


winWindow::winWindow(const std::string &title, float width, float height) : Window(title, width, height) {
    printf("\nRUN winWindow\n");
    this->width = width;
    this->height = height;
    ///////////////////////////

//    SkPixmap pixels;

//    surface->peekPixels(&pixels);/

//    pixelsAddr = pixels.addr();

    bmi = CreateBitmapInfo(width, height);


    /////////////////////

    this->addAsyncTask(CreateWindowsWindows, title, width, height, this);

    auto self = this;
    this->addResizeEvent([self](Element *element, float width, float height) {
//        SkPixmap pixels;

//        surface->peekPixels(&pixels);

//        pixelsAddr = pixels.addr();

        self->bmi = CreateBitmapInfo(static_cast<int>(width), static_cast<int>(height));
    });
    printf("\nASYNC WINDOWWWWWWWWWWWWWWW\n");

};

//winWindow::winWindow(const std::string &title, float width, float height) {
//
//};

void winWindow::refreshFrame() {
    printf("refreshFrame");
}

void winWindow::WinSetDIBitsToDevice(HDC hdc) {

//    printf("\nღღღღღღღღღღღღღღღღღღღღღღღ: width: %.2f, height: %.2f \n", this->width, this->height);
    SetDIBitsToDevice(hdc, 0, 0, this->width, this->height, 0, 0, 0, this->height, this->pixels.addr(),
                      &bmi, DIB_RGB_COLORS);
}
