#include <iostream>
#include <X11/Xlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {

    Display *d = XOpenDisplay(0);

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
    }

    return 0;
}
