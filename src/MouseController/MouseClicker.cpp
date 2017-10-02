#include "../../include/X11/Xlib.h"
#include "../../include/X11/Xutil.h"
#include "../../include/X11/extensions/XTest.h"
#include "../../include/cstring"
#include "DisplayController.h"
#include "MouseClicker.h"

void MouseClicker::mouseButton(int button, bool down) {
    Display *display = DisplayController::getInstance().getDisplay();
    XTestFakeButtonEvent(display, button, down, CurrentTime);
    XFlush(display);
}

void MouseClicker::mouseUp(int button) {
  MouseClicker::mouseButton(button, false);
}

void MouseClicker::mouseDown(int button) {
  MouseClicker::mouseButton(button, true);
}
