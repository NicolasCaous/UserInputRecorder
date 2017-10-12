#include "../../include/X11/Xlib.h"
#include "../../include/X11/Xutil.h"
#include "../../include/X11/extensions/XTest.h"
#include "../../include/cstring"
#include "DisplayController.h"
#include "MouseClicker.h"

void MouseClicker::mouseButton(int button, bool down) {
    bool press = false;
    switch (button) {
        case Button1:
            if (down != MouseClicker::lbState) {
                MouseClicker::lbState = down;
                press = true;
            }
        break;
        case Button2:
            if (down != MouseClicker::rbState) {
                MouseClicker::rbState = down;
                press = true;
            }
        break;
        case Button3:
            if (down != MouseClicker::mbState) {
                MouseClicker::mbState = down;
                press = true;
            }
        break;
    }
    if (press) {
        Display *display = DisplayController::getInstance().getDisplay();
        XTestFakeButtonEvent(display, button, down, CurrentTime);
        XFlush(display);
    }
}

void MouseClicker::mouseUp(int button) {
    MouseClicker::mouseButton(button, false);
}

void MouseClicker::mouseDown(int button) {
    MouseClicker::mouseButton(button, true);
}

bool MouseClicker::lbState = false;
bool MouseClicker::rbState = false;
bool MouseClicker::mbState = false;
