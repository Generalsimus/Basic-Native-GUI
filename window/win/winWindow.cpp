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
    // CreateWindowsWindows(title,width,height, this);
    auto self = this;

    /// futures.push_back(std::async(std::launch::async, ));
    /*std::async(std::launch::async,[&title, &width, &height, &self]{
        printf("RUN ASWWWWWWWWWWWWWWWWWWWWW\n");
        CreateWindowsWindows(title, width, height, self);
        printf("RUN ASWWWWWVVVVVVVVVVVVVVVV\n");
    });*/
     this->addAsyncTask(CreateWindowsWindows, title, width, height, self);
//    this->addAsyncTask([&title, &width, &height, &self] {
//        printf("RUN ASWWWWWWWWWWWWWWWWWWWWW\n");
//        CreateWindowsWindows(title, width, height, self);
//        printf("RUN ASWWWWWVVVVVVVVVVVVVVVV\n");
//    });
    /*this->asyncCall();*/


    printf("\nASYNC WINDOWWWWWWWWWWWWWWW\n");

};


void winWindow::refreshFrame() {
    printf("refreshFrame");
};