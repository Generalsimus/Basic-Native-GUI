#include "./window/win/winWindow.cpp"
#include "./gui/element.cpp"


int main() {

    Element *mainElement3233 = new Element(
            new Element(),
            new Element()
    );


    printf("EEEEE");
    winWindow window("My Custom Window", 900, 600);

    printf("eeerrrrrrrrrrtttttttttttttttttt");
    window.addTouchEvent([](int x, int y) {
        printf("\nCLICKED: x: %d, y: %d \n", x, y);
    });


    window.awaitAll();
    return 0;
};