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
    printf("EEEEE");
//    auto windowObj = new winWindow("My Custom Window", 900.0f, 600.0f);
    auto windowObj = new winWindow("My Custom Window", 900.0f, 600.0f);

    printf("eeerrrrrrrrrrtttttttttttttttttt");

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
//        std::cout << "addTouchDownEventwq3116165\n" << std::endl;
//    });
    windowObj->addChild(
            Element()->setPaints(
                    BoxPercent(100,100),
                    Cursor(Cursor::Arrow)
            ),
            Element()->setPaints(
                    BoxPercent(100, 100)
            )
    )->setPaints(
//            BoxPercent(100, 98),
            DirectionRow()
//            ,
//            Cursor(Cursor::Arrow)
    )->dispatchSetBackgroundColorEvent(SkColorSetARGB(255, 0, 128, 0));

//    while(true){
//
//    }
    awaitAllAsyncTasks();
    return 0;
}