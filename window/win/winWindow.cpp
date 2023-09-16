//
// Created by PC on 9/3/2023.
//

#include "winWindow.h"
#include "../window.cpp"
#include <windows.h>
#include "utils.cpp"


winWindow::winWindow(const std::string &title, int width, int height) : Window(title, width, height) {
    printf("\nRUN winWindow\n");
    this->width = width;
    this->height = height;
    ///////////////////////////

    SkPixmap pixels;

    surface->peekPixels(&pixels);

    pixelsAddr = pixels.addr();

    bmi = CreateBitmapInfo(width, height);


    /////////////////////

    /// futures.push_back(std::async(std::launch::async, ));
    this->addAsyncTask(CreateWindowsWindows, title, width, height, this);



    printf("\nASYNC WINDOWWWWWWWWWWWWWWW\n");

};


void winWindow::refreshFrame() {
    printf("refreshFrame");
}

void winWindow::WinSetDIBitsToDevice(HDC hdc) {

    SetDIBitsToDevice(hdc, 0, 0, this->width, this->height, 0, 0, 0, this->height, this->pixelsAddr,
                      &bmi, DIB_RGB_COLORS);
};