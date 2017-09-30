#include "../../include/X11/Xlib.h"

#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

class DisplayController {
    public:
        static DisplayController& getInstance(void);
        ~DisplayController(void);
        Display* getDisplay(void) const;
    private:
        DisplayController(void);
        DisplayController(const DisplayController&);
        DisplayController& operator= (const DisplayController&);
        Display* display;
    protected:
};

#endif
