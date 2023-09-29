


BITMAPINFO CreateBitmapInfo(int width, int height) {
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down image
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;

    return bmi;
};


typedef void (*SetEventActiveStatus)(bool status);

template<typename CallMe>
using AddEventCallBackType = SetEventActiveStatus (*)(CallMe callBack);


typedef void (*OnPaintEventType)();

//AddEventCallBackType<OnPaintEventType> addEventListener = CreateEventChain<OnPaintEventType>();




LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    winWindow *window = (winWindow *) GetWindowLongPtr(hwnd, GWLP_USERDATA);


    switch (msg) {
        case WH_KEYBOARD_LL: {
            printf("WH_KEYBOARD_LL\n");

            return 0;
        }
        case WM_PAINT: {
            printf("WM_PAINT\n");

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

//            RECT rect;
//            GetWindowRect(hwnd, &rect);


            SkCanvas *canvas = window->surface->getCanvas();

            // Draw something on the SkCanvas
            SkPaint paint;

            auto awaitProcess = window->CreateAwaitGroup();
            window->dispatchDrawEvent(canvas, &paint);
            awaitProcess();

            window->WinSetDIBitsToDevice(hdc);

            // Clean up
            EndPaint(hwnd, &ps);
            return 0;
        };
        case WM_SIZING: {
            printf("WM_SIZING\n");

            RECT *rect2 = reinterpret_cast<RECT *>(lParam);

            auto awaitProcess = window->CreateAwaitGroup();
            window->dispatchResizeEvent(static_cast<float>(rect2->right - rect2->left), static_cast<float>(rect2->bottom - rect2->top));
            awaitProcess();

            return 0;
        }
//////////////////////////////
        case WM_LBUTTONDOWN:
            window->dispatchTouchDownEvent(LOWORD(lParam), HIWORD(lParam), 0);
            return 0;
        case WM_MBUTTONDOWN:
            window->dispatchTouchDownEvent(LOWORD(lParam), HIWORD(lParam), 1);
            return 0;
        case WM_RBUTTONDOWN:
            window->dispatchTouchDownEvent(LOWORD(lParam), HIWORD(lParam), 2);
            return 0;
        case WM_XBUTTONDOWN:
            window->dispatchTouchDownEvent(LOWORD(lParam), HIWORD(lParam), 2 + GET_XBUTTON_WPARAM(wParam));
            return 0;
//////////////////////////////
        case WM_LBUTTONUP:
            window->dispatchTouchUpEvent(LOWORD(lParam), HIWORD(lParam), 0);
            return 0;
        case WM_MBUTTONUP:
            window->dispatchTouchUpEvent(LOWORD(lParam), HIWORD(lParam), 1);
            return 0;
        case WM_RBUTTONUP:
            window->dispatchTouchUpEvent(LOWORD(lParam), HIWORD(lParam), 2);
            return 0;
        case WM_XBUTTONUP:
            window->dispatchTouchUpEvent(LOWORD(lParam), HIWORD(lParam), 2 + GET_XBUTTON_WPARAM(wParam));
            return 0;
//        case WM_KEYDOWN:
//            printf("WM_KEYDOWN\n");
//            return 0;
//        case WM_CHAR:
            // Handle character input event (e.g., typed characters)
        case WM_KEYDOWN:
            printf("WM_KEYDOWN  \n");
            // Handle keydown event
            window->dispatchKeyDownEvent(static_cast<int>(wParam));
            return 0;
        case WM_KEYUP: {
            printf("WM_KEYUP  \n");
            // Handle keydown event
//            wchar_t wstr = static_cast<wchar_t>(wParam);
////            printf("WRITE: %s \n", static_cast<wchar_t>(wParam));
//            std::wstring wideStr(1, wstr);
//
//            // Convert std::wstring to std::string
//            std::string str(wideStr.begin(), wideStr.end());
//
//            printf("str::str::str: %s \n", str.c_str());
//            std::wcout << L"Console Output: " << wstr << std::endl;
            window->dispatchKeyUpEvent(static_cast<int>(wParam));
            return 0;
        }
        case WM_MOUSELEAVE: {
            printf("WM_MOUSELEAVE\n");
            window->dispatchTouchLeaveEvent();

            return 0;
        };
//            /*  case WM_MOUSEHOVER: {
//                  printf("WM_MOUSEHOVER\n");
//
//                  return 0;
//              };*/
        case WM_SETFOCUS:
            printf("WM_SETFOCUS\n");
            return 0;
        case WM_KILLFOCUS:
            printf("WM_KILLFOCUS\n");
            return 0;
        case WM_MOUSEMOVE: {
            // printf("WM_MOUSEMOVE\n");

            window->dispatchTouchMoveEvent(LOWORD(lParam), HIWORD(lParam));

//            return 0;

////////////////////////////////////
//            HCURSOR customCursor2 = LoadCursor(NULL, IDC_ARROW); // Replace with your custom cursor

            // Change the cursor
//            SetCursor(customCursor2);
//            SendMessage(hwnd, WM_SETCURSOR, (WPARAM) hwnd, MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));
////////////////////////////////////

            // Change the cursor when the mouse moves
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE;
            tme.dwHoverTime = 1; //How long the mouse has to be in the window to trigger a hover event.
            tme.hwndTrack = hwnd;
            TrackMouseEvent(&tme);
            return 0;
        };
        case WM_CLOSE: {
            printf("WM_CLOSE\n");
            DestroyWindow(hwnd);
            return 0;
        };
        case WM_DESTROY:
            printf("WM_DESTROY\n");

            PostQuitMessage(0);
            return 0;
            /* case WM_CREATE: {
                 printf("WM_CREATE\n");

                 TRACKMOUSEEVENT mouseEvt;
                 ZeroMemory(&mouseEvt,
                            sizeof(TRACKMOUSEEVENT));

                 mouseEvt.
                         cbSize = sizeof(TRACKMOUSEEVENT);
                 mouseEvt.
                         dwFlags = TME_LEAVE | TME_NONCLIENT;
     //mouseEvt.dwHoverTime = HOVER_DEFAULT;
                 mouseEvt.hwndTrack = hwnd;

                 TrackMouseEvent(&mouseEvt);

                 return 0;
             };*/
        default:
//printf("Received message: 0x%X\n", msg);

            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
};


WNDCLASS CreateWNDCLASS(const std::string &title) {
    WNDCLASS wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;

    wc.hInstance = GetModuleHandle(NULL);
    wc.hbrBackground = (HBRUSH) (COLOR_BACKGROUND);
    wc.lpszClassName = title.c_str();
    if (!RegisterClass(&wc)) {
        printf("CreateWNDCLASS() ERROR\n");
    }
    return wc;
};


void CreateWindowsWindows(const std::string &title, float width, float height, winWindow *window) {
    WNDCLASS wc = CreateWNDCLASS(title);
    HWND hwnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             static_cast<int>(width),
                             static_cast<int>(height), NULL, NULL, wc.hInstance, NULL);

//    static_cast<int>(width) static_cast<int>(width)
    if (!hwnd) {
        printf("CreateWindow() ERROR\n");
        return;
    }
    window->hwnd = hwnd;
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) window);
    RegisterTouchWindow(hwnd, 0);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;

    while (GetMessage(&msg, hwnd, 0, 0)) {

        auto awaitProcess = window->CreateAwaitGroup();
        //std::cout << "Async lambda function running.222" << std::endl;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        awaitProcess();
    };
}
