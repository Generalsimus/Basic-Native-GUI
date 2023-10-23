

#include "include/core/SkCanvas.h"
#include <functional>
#include "../utils/Chain.h"
//
//Chain

// template <typename... Args> class Event {
//   Event() {}
// };

class ElementView;

template<typename... Args>
using EventDefaultChain = Chain<ElementView *, Args...>;

/// Touch EVENTS //
using TouchMoveEventChain = EventDefaultChain<float, float>;
using TouchMoveEventType = TouchMoveEventChain::ChainCallFunctionType;
using TouchOverEventChain = EventDefaultChain<>;
using TouchOverEventType = TouchOverEventChain::ChainCallFunctionType;
using TouchLeaveEventChain = EventDefaultChain<>;
using TouchLeaveEventType = TouchLeaveEventChain::ChainCallFunctionType;

using TouchEvent = EventDefaultChain<float, float, int>;

using TouchDownEventChain = TouchEvent;
using TouchDownEventType = TouchDownEventChain::ChainCallFunctionType;
using TouchUpEventChain = TouchEvent;
using TouchUpEventType = TouchUpEventChain::ChainCallFunctionType;
using TouchEventChain = TouchEvent;
using TouchEventType = TouchEventChain::ChainCallFunctionType;

/// KEYBOARD EVENTS //
using KeyEvent = EventDefaultChain<int>;

using KeyDownEventChain = KeyEvent;
using KeyDownEventType = KeyDownEventChain::ChainCallFunctionType;
using KeyUpEventChain = KeyEvent;
using KeyUpEventType = KeyUpEventChain::ChainCallFunctionType;
using KeyEventChain = KeyEvent;
using KeyEventType = KeyEventChain::ChainCallFunctionType;

/// Draw EVENTS //
using DrawEventChain = EventDefaultChain<SkCanvas *, SkPaint *>;
using DrawEventType = DrawEventChain::ChainCallFunctionType;

/// Set Paints EVENTS //
using SetPaintsEventChain = EventDefaultChain<>;
using SetPaintsEventType = SetPaintsEventChain::ChainCallFunctionType;

/// Resize EVENTS//
using ResizeEventChain = EventDefaultChain<float, float>;
using ResizeEventType = ResizeEventChain::ChainCallFunctionType;

/// CHILD EVENTs //
using AddChildEventChain = EventDefaultChain<ElementView *>;
using AddChildEventType = AddChildEventChain::ChainCallFunctionType;
using RemoveChildEventChain = EventDefaultChain<int, int>;
using RemoveChildEventType = RemoveChildEventChain::ChainCallFunctionType;
using ReplaceChildEventChain =
        EventDefaultChain<int, ElementView *, ElementView *>;
using ReplaceChildEventType = ReplaceChildEventChain::ChainCallFunctionType;

/// SetBackground
using SetBackgroundColorEventChain = EventDefaultChain<SkColor>;
using SetBackgroundColorEventType = SetBackgroundColorEventChain::ChainCallFunctionType;

/// MountOnThree
using MountOnThreeEventChain = EventDefaultChain<ElementView *>;
using MountOnThreeEventType = MountOnThreeEventChain::ChainCallFunctionType;
using UnmountOnThreeEventChain = EventDefaultChain<ElementView *>;
using UnmountOnThreeEventType = UnmountOnThreeEventChain::ChainCallFunctionType;

/////////////////
