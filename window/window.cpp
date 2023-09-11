//
// Created by PC on 8/31/2023.
//
#include "event.cpp"
#include "window.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include <stdlib.h>


int idAs = 0;

Window::Window(const std::string &title, int width, int height): Event(), mainElement(nullptr) {
    printf("\nRUN Window\n");

    this->surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));

    this->id = idAs++;

    printf("\n WINDOW ID: %d \n", this->id);
}

void Window::setMainElement(Element *element) {
    *mainElement = *element;
    element->window = this;
}

void Window::refreshFrame() {

}
