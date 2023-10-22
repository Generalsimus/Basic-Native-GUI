


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


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    winWindow *window = (winWindow *) GetWindowLongPtr(hwnd, GWLP_USERDATA);

//  printf("WndProc\n");

    switch (msg) {
        case WH_KEYBOARD_LL: {
          //  printf("WH_KEYBOARD_LL\n");

            return 0;
        };
        case WM_PAINT: {
           // printf("refreshFrame\n");
            PAINTSTRUCT ps;

            HDC hdc = BeginPaint(window->hwnd, &ps);

            SetDIBitsToDevice(hdc, 0, 0, window->width, window->height, 0, 0, 0, window->height, window->pixels.addr(),
                              &window->bmi, DIB_RGB_COLORS);
            // Clean up
            EndPaint(hwnd, &ps);
            return 0;
        };
        case WM_SIZE: {
           // printf("WM_SIZE\n");
            float width = static_cast<float>(LOWORD(lParam));
            float height = static_cast<float>(HIWORD(lParam));
//            printf("width: %d,height: %d\n", width, height);
            if (width < 1) {
                width = 1;
            }
            if (height < 1) {
                height = 1;
            }
            auto awaitProcess = CreateAsyncAwaitGroup();
//m
            window->dispatchResizeEvent(width, height);
//
            awaitProcess();
//


            auto awaitProcess2 = CreateAsyncAwaitGroup();
//
//            window->draw();
//
            awaitProcess2();
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
            // printf("WM_KEYDOWN  \n");
            // Handle keydown event
            window->dispatchKeyDownEvent(static_cast<int>(wParam));
            return 0;
        case WM_KEYUP: {
            // printf("WM_KEYUP  \n");
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
            // printf("WM_MOUSELEAVE\n");
            window->dispatchTouchLeaveEvent();

            return 0;
        };
//            /*  case WM_MOUSEHOVER: {
//                  printf("WM_MOUSEHOVER\n");
//
//                  return 0;
//              };*/
        case WM_SETFOCUS:
            // printf("WM_SETFOCUS\n");
            return 0;
        case WM_KILLFOCUS:
            //printf("WM_KILLFOCUS\n");
            return 0;
        case WM_MOUSEMOVE: {
            // printf("WM_MOUSEMOVE\n");
//            window->isMouseOver = true;
            window->dispatchTouchMoveEvent(LOWORD(lParam), HIWORD(lParam));
//            window->dispatchTouchOverEvent();
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
            // ("WM_CLOSE\n");
            DestroyWindow(hwnd);
            return 0;
        };
        case WM_DESTROY:
            //printf("WM_DESTROY\n");

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


void CreateWindowsWindows(const std::string &title, float windowWidth, float windowHeight, winWindow *window) {
    WNDCLASS wc = CreateWNDCLASS(title);
    HWND hwnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW | WS_SIZEBOX, CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             static_cast<int>(windowWidth),
                             static_cast<int>(windowHeight), NULL, NULL, wc.hInstance, NULL);

//    static_cast<int>(width) static_cast<int>(width)
    if (!hwnd) {
        printf("CreateWindow() ERROR\n");
        return;
    }
    window->hwnd = hwnd;
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) window);
    RegisterTouchWindow(hwnd, 0);

    ShowWindow(hwnd, SW_SHOW);

////
//    RECT clientRect;
//    GetClientRect(hwnd, &clientRect);
//
//    auto awaitGroup = CreateAsyncAwaitGroup();
//
//    window->dispatchResizeEvent(static_cast<float>(clientRect.right - clientRect.left),
//                                static_cast<float>(clientRect.bottom - clientRect.top));
//    awaitGroup();
//    window->dispatchDrawEvent();

//        printf("WINDOW WHILE 111\n");
    MSG msg;
    while (GetMessage(&msg, hwnd, 0, 0)) {
//        printf("WINDOW WHILE \n");
//        auto awaitProcess = CreateAsyncAwaitGroup();
        //std::cout << "Async lambda function running.222" << std::endl;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
//        awaitProcess();
    };
}
