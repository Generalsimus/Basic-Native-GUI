//
// Created by PC on 9/3/2023.
//

#ifndef CUDA_NEU_WINWINDOW_H
#define CUDA_NEU_WINWINDOW_H
#include <windows.h>
#include "../window.h"

class winWindow : public Window {
public:
    winWindow(const std::string &title, int width, int height) ;

private:
    HWND hwnd;
};


#endif //CUDA_NEU_WINWINDOW_H
