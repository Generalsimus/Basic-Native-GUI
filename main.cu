//#include "window/element.cpp"
#include "./window/win/winWindow.cpp"
#include "./Painters.cpp"
#include <iostream>


auto Element() {
    return new ElementView();
}

template<typename... Args>
auto Element(ElementView *first, Args... args) {
    printf("RUN Elem() D\n");

    return new ElementView(first, std::forward<Args>(args)...);
}

int main() {
    printf("EEEEE\n");
//    auto windowObj = new winWindow("My Custom Window", 900.0f, 600.0f);
    auto windowObj = new winWindow("My Custom Window", 900.0f, 600.0f);

//    printf("eeerrrrrrrrrrtttttttttttttttttt");

//    std::function < void() > removeEvent = []() {
//
//        std::cout << "REMOVED EVENT RRRR\n" << std::endl;
//    };
//    windowObj->addTouchDownEvent([](ElementView *element, float x, float y, int type) {
//
//        std::cout << "addTouchDownEvent333 RRRR\n" << std::endl;
//    }, removeEvent);
//    windowObj->addTouchUpEvent([removeEvent](ElementView *element, float x, float y, int type) mutable {
//        removeEvent();
//        std::cout << "addTouchDownEventwq3116165\n" << std::endl;dispatchTouchDownEvent
//    });
    windowObj->addChild(
            Element()->setPaints(
                    Box(),
                    Cursor(Cursor::Text)
            )->dispatchSetBackgroundColorEvent(
                    SkColorSetARGB(255, 0, 0, 255)
            ),
            Element()->setPaints(
                    Text("Hello"),
//                    BoxPercent(50, 50),
                    Cursor(Cursor::Arrow)
            )->addTouchDownEvent([](ElementView *element, float x, float y, int type) {

                std::cout << "TOUCH DOWN AT: " << element->id << std::endl;
            })
    )->setPaints(
            Box(),
            Cursor(Cursor::Arrow),
            DirectionRow()
    )->dispatchSetBackgroundColorEvent(
            SkColorSetARGB(255, 0, 128, 0)
    );




//    while(true){
//
//    }
    awaitAllAsyncTasks();
    return 0;
}