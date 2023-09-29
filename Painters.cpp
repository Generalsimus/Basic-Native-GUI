


auto BoxPx(float width, float height) {
    return [width, height](Element *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        element->addDrawEvent([width, height](Element *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(SK_ColorRED);
            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, width, height), *paint);

        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent](Element *element) {
            (*removeEvent)();
            delete removeEvent;
        }, *removeEvent);
    };
};

auto BoxPercent(float percentWidth, float percentHeight) {
    return [percentWidth, percentHeight](Element *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        element->addDrawEvent([percentWidth, percentHeight](Element *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(SK_ColorRED);
            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, (percentWidth / 100.0f) * element->width,
                                              (percentHeight / 100.0f) * element->height), *paint);
        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent](Element *element) {
            (*removeEvent)();
            delete removeEvent;
        }, *removeEvent);
    };
};

auto FullBox() {
    return [](Element *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        element->addDrawEvent([](Element *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(SK_ColorRED);
            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, element->width, element->height), *paint);
        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent](Element *element) {
            (*removeEvent)();
            delete removeEvent;
        }, *removeEvent);
    };
};