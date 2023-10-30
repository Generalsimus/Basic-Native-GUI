# [Skia Example](https://skia.org)


<details>

<summary>Example</summary>

```cpp
#include "./window/win/winWindow.cpp"
#include "./Painters.cpp"
#include <iostream>

int main()
{

    auto windowObj = new winWindow("My Custom Window", 500.0f, 500.0f);

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
``` 
</details>

<details>

<summary>Element Events</summary>


|                                           Add Event                                            |           Run Event            | 
|:----------------------------------------------------------------------------------------------:|:------------------------------:|
|          ```addTouchMoveEvent(TouchMoveEventType &&, RemoveEventCallBack &&, bool)```          | ```dispatchTouchMoveEvent()``` | 
|          ```addTouchOverEvent(TouchOverEventType &&, RemoveEventCallBack &&, bool)```          | ```dispatchTouchOverEvent()``` | 
|         ```addTouchLeaveEvent(TouchLeaveEventType &&, RemoveEventCallBack &&, bool)```         | ```dispatchTouchLeaveEvent()``` | 
|          ```addTouchDownEvent(TouchDownEventType &&, RemoveEventCallBack &&, bool)```          | ```dispatchTouchDownEvent()``` | 
|            ```addTouchUpEvent(TouchUpEventType &&, RemoveEventCallBack &&, bool)```            | ```dispatchTouchUpEvent()``` | 
|              ```addTouchEvent(TouchEventType &&, RemoveEventCallBack &&, bool)```              | ```dispatchTouchEvent()``` | 
|            ```addKeyDownEvent(KeyDownEventType &&, RemoveEventCallBack &&, bool)```            | ```dispatchKeyDownEvent()``` | 
|              ```addKeyUpEvent(KeyUpEventType &&, RemoveEventCallBack &&, bool)```              | ```dispatchKeyUpEvent()``` | 
|                ```addKeyEvent(KeyEventType &&, RemoveEventCallBack &&, bool)```                | ```dispatchKeyEvent()``` | 
|               ```addDrawEvent(DrawEventType &&, RemoveEventCallBack &&, bool)```               | ```dispatchDrawEvent()``` | 
|             ```addResizeEvent(ResizeEventType &&, RemoveEventCallBack &&, bool)```             | ```dispatchResizeEvent()``` | 
|          ```addSetPaintsEvent(SetPaintsEventType &&, RemoveEventCallBack &&, bool)```          | ```dispatchSetPaintsEvent()``` | 
|           ```addAddChildEvent(AddChildEventType &&, RemoveEventCallBack &&, bool)```           | ```dispatchAddChildEvent()``` | 
|        ```addRemoveChildEvent(RemoveChildEventType &&, RemoveEventCallBack &&, bool)```        | ```dispatchRemoveChildEvent()``` | 
|       ```addReplaceChildEvent(RemoveChildEventType &&, RemoveEventCallBack &&, bool)```        | ```dispatchReplaceChildEvent()``` | 
| ```addSetBackgroundColorEvent(SetBackgroundColorEventType &&, RemoveEventCallBack &&, bool)``` | ```dispatchSetBackgroundColorEvent()``` | 
|       ```addMountOnThreeEvent(MountOnThreeEventType &&, RemoveEventCallBack &&, bool)```       | ```dispatchMountOnThreeEvent()``` | 
|    ```addUnmountOnThreeEvent(UnmountOnThreeEventType &&, RemoveEventCallBack &&, bool)```      | ```dispatchUnmountOnThreeEvent()``` | 
|    ```addUnmountOnThreeEvent(UnmountOnThreeEventType &&, RemoveEventCallBack &&, bool)```      | ```dispatchUnmountOnThreeEvent()``` | 



</details>


<details>

<summary>Element Painters</summary>


</details>

<details>

<summary>Element Style</summary>


</details>