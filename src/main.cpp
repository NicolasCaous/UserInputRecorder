#include "../include/iostream"
#include "../include/unistd.h"
#include "MouseTracker.h"

int main(int argc, char ** argv) {

    MouseTracker* mt1 = MouseTracker::getInstance();
    MouseTracker* mt2 = MouseTracker::getInstance();

    while(true) {
        //sleep(1);
        std::cout << mt1->getCoordinates().x << std::endl;
        std::cout << mt2->getCoordinates().y << std::endl;
    }

    /*Display *d = XOpenDisplay(0);

    if (d) {
        Window root_window;
        root_window = XRootWindow(d, 0);
        XWarpPointer(
            d, None, root_window,
            0, 0, 0, 0,
            -1920, -1920
        );
        XFlush(d);
        sleep(1);
        XWarpPointer(
            d, None, root_window,
            0, 0, 0, 0,
            1920, 1920
        );
        XFlush(d);
    }*/

    return 0;
}
