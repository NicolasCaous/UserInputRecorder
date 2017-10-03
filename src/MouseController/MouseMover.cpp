#include "../../include/X11/Xlib.h"
#include "../../include/cstring"
#include "DisplayController.h"
#include "MouseMover.h"

void MouseMover::move(XY coord) {
    XWarpPointer(
        DisplayController::getInstance().getDisplay(), None,
        XRootWindow(DisplayController::getInstance().getDisplay(), 0),
        0, 0, 0, 0,
        coord.x, coord.y
    );
    DisplayController::getInstance().flush();
}
