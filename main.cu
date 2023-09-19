#include "window/element.cpp"
#include "./window/win/winWindow.cpp"

int main() {

    auto mainElement3233 = new Element(
            new Element(),
            new Element()
    );


    printf("EEEEE");
    winWindow window("My Custom Window", 900, 600);

    printf("eeerrrrrrrrrrtttttttttttttttttt");
    window.addTouchEvent([](Element *element, int x, int y) {
        printf("\nCLICKED: x: %d, y: %d \n", x, y);
    });
//    auto eeee = [](Element *element, int x, int y) {
//        printf("\nAAAA: x: %d, y: %d \n", x, y);
//    };
//
//    window.addTouchEvent(eeee);
    window.addTouchEvent([](Element *element, int x, int y) {
        printf("\nAAAA: x: %d, y: %d \n", x, y);
    });
    window.addTouchEvent([](Element *element, int x, int y) {
        printf("\nEEEEE: x: %d, y: %d \n", x, y);
    });

//    window.dispatchEvent("touchDown", 1, 2);
//    window.addTouchEvent([](Element* element, int x, int y) {
//        printf("\nAAAA: x: %d, y: %d \n", x, y);
//    });
    window.dispatchTouchEvent(2, 5);


    window.awaitAll();
    return 0;
};