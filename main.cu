#include "./window/win/winWindow.cpp"
#include "./gui/element.cpp"


int main() {

    Element mainElement = Element(
            Element(
                    Element(
                            Element(),
                            Element(),
                            Element()
                    )
            )
    );

    winWindow window = winWindow("My Custom Window", 900, 600);


    return 0;
};