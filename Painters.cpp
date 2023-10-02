


auto BoxPx(float width, float height) {
    return [width, height](ElementView *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        element->addDrawEvent([width, height](ElementView *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(SK_ColorRED);
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
        element->addDrawEvent([percentWidth, percentHeight](ElementView *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(SK_ColorRED);
            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, (percentWidth / 100.0f) * element->width,
                                              (percentHeight / 100.0f) * element->height), *paint);
        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent](ElementView *element) {
            (*removeEvent)();
            delete removeEvent;
        }, *removeEvent);
    };
};

auto FullBox() {
    return [](ElementView *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };
        element->addDrawEvent([](ElementView *element, SkCanvas *canvas, SkPaint *paint) {

            paint->setColor(SK_ColorWHITE);
            canvas->drawRect(SkRect::MakeXYWH(element->x, element->y, element->width, element->height), *paint);
        }, *removeEvent);
        element->addSetPaintsEvent([removeEvent](ElementView *element) {
            (*removeEvent)();
            delete removeEvent;
        }, *removeEvent);
    };
};

auto DirectionRow() {
    return [](ElementView *element) {
        std::function < void() > *removeEvent = new std::function<void()>;
        *removeEvent = []() {

        };

        std::function<void(ElementView *element)> makeAlignmend = [](ElementView *element){
            float startAt = element->x;

            for (ElementView *child: element->children){
                child->x = startAt;
                child->y = element->y;
                startAt = startAt+ element->width;
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