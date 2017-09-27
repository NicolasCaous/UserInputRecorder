#include "DisplayController.h"
#include "../../include/cstddef"
#include "../../include/X11/Xlib.h"

DisplayController* DisplayController::getInstance(void) {
    if (DisplayController::displayController == NULL)
    {
        DisplayController::displayController = new DisplayController;
    }
    return DisplayController::displayController;
}

Display* DisplayController::getDisplay(void) {
    return this->display;
}

DisplayController::DisplayController(void) {
    this->display = XOpenDisplay(0);
}

DisplayController* DisplayController::displayController;
