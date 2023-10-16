//#include "window/element.cpp"
#include "./window/win/winWindow.cpp"
#include "./Painters.cpp"


auto Element() {
    return new ElementView();
}

template<typename... Args>
auto Element(ElementView *first, Args... args) {
    printf("RUN Elem() D\n");

    return new ElementView(first, std::forward<Args>(args)...);
}

int main() {
//    auto mainElement3233 = Element(
//            Element()->setPaints(FullBox(), DirectionRow()),
//            Element()
//    );

    printf("EEEEE");
    auto windowObj = new winWindow("My Custom Window", 900.0f, 600.0f);

    printf("eeerrrrrrrrrrtttttttttttttttttt");
    windowObj->addChild(
            Element()->setPaints(
                    BoxPercent(100, 50),
                    Cursor(Cursor::Arrow)
            ),
            Element()->setPaints(
                    BoxPercent(100, 100)
            )
    )->setPaints(
            BoxPercent(100, 98),
            DirectionRow()
//            ,
//            Cursor(Cursor::Arrow)
    )->dispatchSetBackgroundColorEvent(SkColorSetARGB(255, 0, 128, 0));


    awaitAllAsyncTasks();
    return 0;
}