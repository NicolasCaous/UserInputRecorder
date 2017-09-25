#include "../include/cstddef"
#include "../include/X11/Xlib.h"
#include "MouseTracker.h"

MouseTracker* MouseTracker::get_instance(void)
{
    if (MouseTracker::tracker == NULL)
    {
        MouseTracker::tracker = new MouseTracker;
    }
    return MouseTracker::tracker;
}

XY MouseTracker::get_coordinates(void)
{
    this->update();
    return this->coordinates;
}

void MouseTracker::update(void)
{
    Display *d = XOpenDisplay(0);

    if (d)
    {
        unsigned int mask_return;
        int winx, winy;
        Window window_returned;
        Window root;

        root = XRootWindow(d, 0);

        XQueryPointer(
            d, root, &window_returned,
            &window_returned, &this->coordinates.x,
            &this->coordinates.y, &winx, &winy,
            &mask_return
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
