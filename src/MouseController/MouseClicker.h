#ifndef MOUSECLICKER_H
#define MOUSECLICKER_H

#include "../../include/X11/Xlib.h"

#define CURRENTWINDOW (0)

class MouseClicker {
    public:
        static void mouseUp(int button);
        static void mouseDown(int button);
    private:
        static void mouseButton(int button, bool down);
    protected:
};

#endif
