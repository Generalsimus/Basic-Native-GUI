//#include "window/element.cpp"
#include "./window/win/winWindow.cpp"
#include "./Painters.cpp"

class El;

class El {
public:
    El();

//    template<typename Elem>
//    El(Elem &&first);

//    El(El &&first);
    template<typename... Args>
    void add(Args... rest);


    void print();
};

El::El() {
    printf("RUN Element() No CHILD\n");
}

//template<typename Elem>
//El::El(Elem &&first) {
//    printf("RUN Element() WITH CHILwwwD\n");
//}

//template<typename... Args>
//void El::add(Args... &rest) {
//    printf("RUN Element() WITH CHILD\n");
//
//}

//El::El(El first) {
//    printf("RUN Element() WITH CHILD\n");
//
//}

//void El::print() {
//    printf("PRINT");
//}
auto Element() {
    return new ElementView();
}

template<typename... Args>
auto Element(ElementView *first, Args... args) {
    printf("RUN Elem() D\n");

    return new ElementView(first, std::forward<Args>(args)...);
}
//Element

int main() {
//    auto mainElement3233 = Element(
//            Element()->setPaints(FullBox(), DirectionRow()),
//            Element()
//    );

    printf("EEEEE");
    winWindow window("My Custom Window", 900.0f, 600.0f);

    printf("eeerrrrrrrrrrtttttttttttttttttt");
    window.addChild(
            Element(
                    Element()->setPaints(FullBox(), DirectionRow()),
                    Element()
            )
    )->setPaints(
            FullBox(),
            DirectionRow()
    );
//    window.setPaints(DrawBox(20, 10));

//    window.addTouchDownEvent([](Element *element, int x, int y, int typeIndex) {
//        printf("\nTOUCH DOWN: x: %d, y: %d typeIndex: %d\n", x, y, typeIndex);
//    });
//    window.addTouchUpEvent([](Element *element, int x, int y, int typeIndex) {
//        printf("\nTOUCH UP: x: %d, y: %d typeIndex: %d\n", x, y, typeIndex);
//    });

//    window.addTouchEvent([](Element *element, int x, int y, int typeIndex) {
//        printf("\nTOUCH EVENT: x: %d, y: %d typeIndex: %d\n", x, y, typeIndex);
//    });
//
//    window.addKeyDownEvent([](Element *element, int keyIndex) {
//        printf("\nKEY DOWN EVENT: KeyIndex: %d\n", keyIndex);
//    });
//
//    window.addKeyUpEvent([](Element *element, int keyIndex) {
//        printf("\nKEY UP EVENT: KeyIndex: %d\n", keyIndex);
//    });

//    window.addTouchOverEvent([](Element *element) {
//        printf("\nTOUCH addTouchOverEvent: \n");
//    });

//    window.dispatchTouchDownEvent(2, 5, 1);

//    std::function < void() > removeEvent = []() {
//
//    };

//    window.addTouchDownEvent([](Element *element, int x, int y, int typeIndex) {
//        printf("\nTOUCH DOWN: x: %d, y: %d typeIndex: %d\n", x, y, typeIndex);
//    }, removeEvent);
//
//    window.addTouchEvent([&removeEvent](Element *element, int x, int y, int typeIndex) {
//        removeEvent();
//        printf("\nTOUCH EVENT: x: %d, y: %d typeIndex: %d\n", x, y, typeIndex);
//    });


    window.awaitAll();
    return 0;
}