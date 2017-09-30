#include "DisplayController.h"
#include "../../include/cstddef"
#include "../../include/iostream"
#include "../../include/X11/Xlib.h"

DisplayController& DisplayController::getInstance(void) {
    static DisplayController instance;
    return instance;
}

DisplayController::~DisplayController(void) {
    XCloseDisplay(DisplayController::getInstance().getDisplay());
}

Display* DisplayController::getDisplay(void) const {
    return this->display;
}

void DisplayController::flush(void) const {
    XFlush(this->display);
}

DisplayController::DisplayController(void) {
    this->display = XOpenDisplay(0);
}
