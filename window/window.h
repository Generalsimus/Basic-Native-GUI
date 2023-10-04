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


class Window : public ElementView {
private:
    DrawEventType DrawEventChain = nullptr;

    ResizeEventType ResizeEventChain = nullptr;
public:
    SkPixmap pixels;
    sk_sp<SkSurface> surface;
    SkPaint paint;

    virtual void refreshFrame();

    /// Draw
    template<typename RemoveEventCallBack = std::function<void()>>
    Window *addDrawEvent(DrawEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Window *dispatchDrawEvent(SkCanvas *canvas, SkPaint *paint);

    /// RESIZE ELEMENT
    template<typename RemoveEventCallBack = std::function<void()>>
    Window *addResizeEvent(ResizeEventType &&callBack, RemoveEventCallBack &&removeEventCallBack = nullptr);

    Window *dispatchResizeEvent(float windowWidth, float windowHeight);

protected:
    Window(const std::string &title, float width, float height);

    void ss() {
//        auto originalSurfacesa = SkImageInfo::MakeN32Premul(width, height));
//        originalSurfacesa.
    }
};


#endif //CUDA_NEU_WINDOW_H
