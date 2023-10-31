//
// Created by PC on 8/31/2023.
//

#ifndef CUDA_NEU_WINDOW_H
#define CUDA_NEU_WINDOW_H

#include <windows.h>
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include <string>
#include <cstddef>
#include <cstdlib>
#include "elementView.h"

enum class Cursor : unsigned int {
    Arrow,
    Wait,
    Text,
    None
};


class Window : public ElementView {

public:
    SkPixmap pixels;

    SkPaint paint;
    sk_sp<SkSurface> surface;


    virtual void refreshFrame();

    virtual std::function<void()> setCursor(ElementView *cursor);
    virtual std::function<void()> setCursor(Cursor cursor);
protected:
    Window(const std::string &title, float windowWidth, float WindowHeight);

    std::function<void()> setCursorFunc= [](){};


};


#endif //CUDA_NEU_WINDOW_H
