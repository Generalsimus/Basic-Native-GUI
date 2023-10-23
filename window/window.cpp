//
// Created by PC on 8/31/2023.
//
#include "window.h"
#include "./elementView.cpp"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"
#include "include/core/SkPaint.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkPath.h"
#include "include/core/SkGraphics.h"
#include <stdlib.h>


Window::Window(const std::string &title, float windowWidth, float windowHeight) : ElementView() {
    //printf("\nRUN Window\n");

    this->window = this;
    this->parent = this;


//    this->surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(windowWidth, windowHeight));
//    this->surface->peekPixels(&this->pixels);
//
//    auto self = this;
//    this->addResizeEvent([self](ElementView *element, float width, float height) {
//
//        self->surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));
//
//        self->surface->peekPixels(&self->pixels);
//    });
//

//    printf("\n WINDOW ID\n");
}

//auto Window::setCursor(ElementView *cursor) {
////    ElementView::setCursor(cursor);
//    return  this;
//}


//auto Window::setCursor(Cursor cursor) {
////    ElementView::setCursor(cursor);
//    return  this;
//}

void Window::refreshFrame() {

}

std::function<void()> Window::setCursor(Cursor cursor) {
    return nullptr;
}

std::function<void()> Window::setCursor(ElementView *cursor) {
    return nullptr;
}
//
//void Window::refreshFrame() {
//
//}
//
