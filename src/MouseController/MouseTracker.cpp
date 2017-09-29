#include "../../include/X11/Xlib.h"
#include "DisplayController.h"
#include "MouseTracker.h"

MouseTracker& MouseTracker::getInstance(void) {
    static MouseTracker instance;
    return instance;
}

MouseTracker::~MouseTracker(void) {
}

XY MouseTracker::getCoordinates(void) const {
    (const_cast< MouseTracker* >(this))->update();
    return this->coordinates;
}

void MouseTracker::update(void) {
    const DisplayController& displayController = DisplayController::getInstance();
    Display* d = displayController.getDisplay();

    unsigned int maskReturn;
    int winx, winy;
    Window windowReturned;
    Window root;

    root = XRootWindow(d, 0);

    XQueryPointer(
        d, root, &windowReturned,
        &windowReturned, &this->coordinates.x,
        &this->coordinates.y, &winx, &winy,
        &maskReturn
    );
}
