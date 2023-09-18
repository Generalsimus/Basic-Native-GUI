


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
        case WM_PAINT: {
            printf("WM_PAINT\n");
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetWindowRect(hwnd, &rect);
/*
            window->width = rect.right - rect.left;
            window->height = rect.bottom - rect.top;*/

            //  sk_sp<SkSurface>* surf = window->surface;

            SkCanvas *canvas = window->surface->getCanvas();



            // Draw something on the SkCanvas (for example, a red rectangle)
            SkPaint paint;
            paint.setColor(SK_ColorRED);
            canvas->drawRect(SkRect::MakeXYWH(100, 100, 200, 200), paint);


            //  SkPixmap pixels = window->pixels;

            //  surf->peekPixels(&pixels);


            // BITMAPINFO bmi = window->bmi;
            window->WinSetDIBitsToDevice(hdc);
            // Release the HDC
//            SetDIBitsToDevice(hdc, 0, 0, window->width, window->height, 0, 0, 0, window->height, window->pixelsAddr,
//                              &bmi, DIB_RGB_COLORS);


            // Clean up
            EndPaint(hwnd, &ps);
            return 0;
        };
        case WM_LBUTTONDOWN: {
            printf("WM_LBUTTONDOWN");


            window->dispatchTouchEvent(LOWORD(lParam), HIWORD(lParam));

//            window->dispatchEvent("touchDown", 23, 44);
            window->dispatchEvent("touchDown", LOWORD(lParam), HIWORD(lParam));
            return 0;
        }
        case WM_MOUSELEAVE: {
            printf("WM_MOUSELEAVE\n");


            return 0;
        };
            /*  case WM_MOUSEHOVER: {
                  printf("WM_MOUSEHOVER\n");

                  return 0;
              };*/
        case WM_SETFOCUS:
            printf("WM_SETFOCUS\n");
            return 0;
        case WM_KILLFOCUS:
            printf("WM_KILLFOCUS\n");
            return 0;
        case WM_MOUSEMOVE: {
            // printf("WM_MOUSEMOVE\n");

            HCURSOR customCursor2 = LoadCursor(NULL, IDC_ARROW); // Replace with your custom cursor

            // Change the cursor
            SetCursor(customCursor2);
            SendMessage(hwnd, WM_SETCURSOR, (WPARAM) hwnd, MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));

            // Change the cursor when the mouse moves
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_HOVER | TME_LEAVE;
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


void CreateWindowsWindows(const std::string &title, int width, int height, winWindow *window) {
    WNDCLASS wc = CreateWNDCLASS(title);
    HWND hwnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width,
                             height, NULL, NULL, wc.hInstance, NULL);


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
        //PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)/**/
        //std::cout << "Async lambda function running.222" << std::endl;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    };
}
