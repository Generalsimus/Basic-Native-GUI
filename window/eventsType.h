

#include "include/core/SkCanvas.h"


class ElementView;

template<typename... Args>
using EventDefaultType = std::function<void(ElementView *, Args... args)>;

/// Touch EVENTS //
using TouchMoveEventType = EventDefaultType<float, float>;
using TouchOverEventType = EventDefaultType<>;
using TouchLeaveEventType = EventDefaultType<>;


using TouchEvent = EventDefaultType<float, float, int>;
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

/// CHILD EVENTs //
using AddChildEventType = EventDefaultType<ElementView *>;
using RemoveChildEventType = EventDefaultType<int, int>;
using ReplaceChildEventType = EventDefaultType<int, ElementView *, ElementView *>;

/// SetBackground
using SetBackgroundColorEventType = EventDefaultType<SkColor>;

/// MountOnThree
using MountOnThreeEventType = EventDefaultType<ElementView *>;
using UnmountOnThreeEventType = EventDefaultType<ElementView *>;


/////////////////
