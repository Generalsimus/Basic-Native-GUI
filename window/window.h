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

public:
    SkPixmap pixels;
    sk_sp<SkSurface> surface;

    virtual void refreshFrame();



protected:
    Window(const std::string &title, float width, float height);

    void ss() {
//        auto originalSurfacesa = SkImageInfo::MakeN32Premul(width, height));
//        originalSurfacesa.
    }
};


#endif //CUDA_NEU_WINDOW_H
