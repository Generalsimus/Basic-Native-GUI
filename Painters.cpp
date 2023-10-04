


auto BoxPx(float width, float height) {
    return [width, height](ElementView *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        element->addDrawEvent([width, height](ElementView *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(SK_ColorRED);
            paint->setStyle(SkPaint::kStrokeAndFill_Style);
            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, width, height), *paint);

        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent](ElementView *element) {
            (*removeEvent)();
            delete removeEvent;
        }, *removeEvent);
    };
};

auto BoxPercent(float percentWidth, float percentHeight) {
    return [percentWidth, percentHeight](ElementView *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        SkColor *bgColor = new SkColor;
        *bgColor = SK_ColorWHITE;
        element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
            *bgColor = color;
        }, *removeEvent);
        element->addDrawEvent(
                [percentWidth, percentHeight, bgColor](ElementView *element, SkCanvas *canvas, SkPaint *paint) {

                    paint->setColor(*bgColor);

                    paint->setStyle(SkPaint::kStrokeAndFill_Style);
                    canvas->drawRect(
                            SkRect::MakeXYWH(element->x, element->y, (percentWidth / 100.0f) * element->parent->width,
                                             (percentHeight / 100.0f) * element->parent->height), *paint);

                }, *removeEvent);
        element->addSetPaintsEvent([removeEvent, bgColor](ElementView *element) {
            (*removeEvent)();
            delete removeEvent;
            delete bgColor;
        }, *removeEvent);
    };
};

auto FullBox() {
    return [](ElementView *element) {
        auto *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        SkColor *bgColor = new SkColor;
        *bgColor = SK_ColorWHITE;
        element->addSetBackgroundColorEvent([bgColor](ElementView *element, SkColor color) {
            *bgColor = color;
        }, *removeEvent);
        element->addDrawEvent([bgColor](ElementView *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(*bgColor);

//            paint->setStyle(SkPaint::kFill_Style);
            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, element->parent->width, element->parent->height),
                             *paint);
        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent, bgColor](ElementView *element) {
            (*removeEvent)();
            delete removeEvent;
            delete bgColor;
        }, *removeEvent);
    };
};

auto DirectionRow() {
    return [](ElementView *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };

        std::function < void(ElementView * element) > makeAlignmend = [](ElementView *element) {
            float startAt = element->x;

            for (ElementView *child: element->children) {
                child->x = startAt;
                child->y = element->y;
                startAt = startAt + element->width;
            }
        };
        element->addAddChildEvent([makeAlignmend](ElementView *element, ElementView *newChild) {
            makeAlignmend(element);
        }, *removeEvent);
        element->addResizeEvent([makeAlignmend](ElementView *element, float width, float height) {
            makeAlignmend(element);
        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent](ElementView *element) {
            (*removeEvent)();
            delete removeEvent;
        }, *removeEvent);
    };
};