//#include "window/element.cpp"
#include "./window/win/winWindow.cpp"
#include "./Painters.cpp"


int main() {

//    auto mainElement3233 = new Element(
//            new Element(),
//            new Element()
//    );


    printf("EEEEE");
    winWindow window("My Custom Window", 900.0f, 600.0f);

    printf("eeerrrrrrrrrrtttttttttttttttttt");
    window.setPaints(FullBox());
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