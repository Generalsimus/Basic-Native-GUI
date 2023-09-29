

#include "include/core/SkCanvas.h"


class Element;

template<typename... Args>
using EventDefaultType = std::function<void(Element*, Args... args)>;

/// Touch EVENTS //
using TouchMoveEventType = EventDefaultType<int, int>;
using TouchOverEventType = EventDefaultType<>;
using TouchLeaveEventType = EventDefaultType<>;


using TouchEvent = EventDefaultType<int, int, int>;
using TouchDownEventType = TouchEvent;
using TouchUpEventType = TouchEvent;
using TouchEventType = TouchEvent;


/// KEYBOARD EVENTS //
using KeyEvent = EventDefaultType<int>;
//        std::function<void(Element *, int)>;

using KeyDownEventType = KeyEvent;
using KeyUpEventType = KeyEvent;
using KeyEventType = KeyEvent;


/// Draw EVENTS //
using DrawEventType = EventDefaultType<SkCanvas *, SkPaint *>;


/// Set Paints EVENTS //
using SetPaintsEventType = EventDefaultType<>;

/// Resize EVENTS//
using ResizeEventType = EventDefaultType<float, float>;
