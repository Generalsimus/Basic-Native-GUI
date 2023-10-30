#include "./window/win/winWindow.cpp"
#include "./Painters.cpp"
#include <iostream>

int main()
{

    auto windowObj = new winWindow("My Custom Window", 500.0 f, 500.0 f);

    windowObj->addChild(
        Element()->setPaints(
            Box(),
            Cursor(Cursor::Pointer)
        ),
        Element()->setPaints(
                     BoxPercent(20, 10),
                     Cursor(Cursor::Text)
        )->addTouchDownEvent([](ElementView *element, float x, float y, int type) {
                 std::cout << "TOUCH DOWN" << std::endl;

        })
    );
}