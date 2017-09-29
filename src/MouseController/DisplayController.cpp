#include "DisplayController.h"
#include "../../include/cstddef"
#include "../../include/iostream"
#include "../../include/X11/Xlib.h"

DisplayController& DisplayController::getInstance(void) {
    static DisplayController instance;
    if (instance.display == NULL) {
        instance.display = XOpenDisplay(0);
    }
    return instance;
}

DisplayController::~DisplayController() {
    XCloseDisplay(DisplayController::getInstance().getDisplay());
}

Display* DisplayController::getDisplay(void) const {
    return this->display;
}
