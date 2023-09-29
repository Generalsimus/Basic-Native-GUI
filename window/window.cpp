//
// Created by PC on 8/31/2023.
//
#include "window.h"
#include "./element.cpp"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include <stdlib.h>


Window::Window(const std::string &title, float width, float height) : Element() {
    printf("\nRUN Window\n");

    this->surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));

    this->surface->peekPixels(&this->pixels);

    auto self = this;
    this->addResizeEvent([self](Element *element, float width, float height) {
        self->width = width;
        self->height = height;
        printf("\nTaddResizeEventN: width: %.5f, height: %.5f \n", width, height);
        self->surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));

        self->surface->peekPixels(&self->pixels);

    });

    printf("\n WINDOW ID\n");
}


void Window::refreshFrame() {

}
