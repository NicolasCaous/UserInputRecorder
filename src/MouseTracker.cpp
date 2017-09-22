#include "../include/cstddef"
#include "../include/X11/Xlib.h"
#include "MouseTracker.h"

MouseTracker* MouseTracker::getInstance(void)
{
    if (MouseTracker::tracker == NULL) {
        MouseTracker::tracker = new MouseTracker;
    }
    return MouseTracker::tracker;
}

XY MouseTracker::getCoordinates(void)
{
    this->update();
    return this->coordinates;
}

void MouseTracker::update(void)
{
    Display *d = XOpenDisplay(0);

    if (d) {
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

    XCloseDisplay(d);
}

MouseTracker::MouseTracker(void)
{
    this->coordinates = *(new XY);
    this->update();
}

MouseTracker* MouseTracker::tracker;
