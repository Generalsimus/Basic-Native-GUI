

BITMAPINFO CreateBitmapInfo(SkBitmap *bitmap, int width, int height) {
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


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM  wParam,  LPARAM lParam) {

    Window *window = (Window *) GetWindowLongPtr(hwnd, GWLP_USERDATA);


    switch (msg) {
        case WM_PAINT: {
            printf("WM_PAINT\n");
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetWindowRect(hwnd, &rect);

            window->width = rect.right - rect.left;
            window->height = rect.bottom - rect.top;


            SkBitmap skBitmap;
            skBitmap.allocN32Pixels(window->width, window->height);  // Width and height of the bitmap
            printf("WORK");
            SkCanvas canvas(skBitmap);

            // Draw something on the SkCanvas (for example, a red rectangle)
            SkPaint paint;
            paint.setColor(SK_ColorRED);
            canvas.drawRect(SkRect::MakeXYWH(100, 100, 200, 200), paint
            );

            const void *pixels = skBitmap.getPixels();

/*            HCURSOR customCursor = LoadCursor(NULL, IDC_ARROW); // Replace with your custom cursor

            // Change the cursor
            SetCursor(customCursor);
            SendMessage(hwnd, WM_SETCURSOR, (WPARAM) hwnd, MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));*/


            BITMAPINFO bmi = CreateBitmapInfo(&skBitmap, window->width, window->height);

            // Release the HDC
            SetDIBitsToDevice(hdc,0, 0, window->width, window->height, 0, 0, 0, window->height, pixels, &bmi, DIB_RGB_COLORS);


            // Clean up
            EndPaint(hwnd, &ps);
            return 0;
        };
        case WM_MOUSELEAVE: {
            printf("WM_MOUSELEAVE\n");


            return 0;
        };
        case WM_MOUSEHOVER: {
            printf("WM_MOUSEHOVER\n");

            return 0;
        };
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
            SendMessage(hwnd, WM_SETCURSOR, (WPARAM)hwnd, MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));

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


WNDCLASS CreateWNDCLASS(const std::string &title ) {
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

