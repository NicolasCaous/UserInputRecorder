#include "../../include/X11/Xlib.h"

#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

class DisplayController {
    public:
        static DisplayController* getInstance(void);
        Display* getDisplay(void);
    private:
        DisplayController(void);
        static DisplayController* displayController;
        Display* display;
    protected:
};

#endif
