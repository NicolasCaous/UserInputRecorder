#include "../../include/iostream"
#include "../../include/cstring"
#include "../../include/X11/Xlib.h"
#include "../ThreadController/ThreadController.h"
#include "DisplayController.h"
#include "MouseEventListener.h"
#include "MouseClicker.h"

MouseEventListener& MouseEventListener::getInstance(void) {
    static MouseEventListener* instance;
    if (instance == NULL) {
        instance = new MouseEventListener;
    }
    return *instance;
}

MouseEventListener::~MouseEventListener(void) {
    this->interrupt = true;
    ThreadController::getInstance().closeThread(this->threadName);
    XUngrabPointer(DisplayController::getInstance().getDisplay(), CurrentTime);
}

XY MouseEventListener::getCoordinates(void) const {
    return this->coordinates;
}

bool MouseEventListener::getLb(void) const {
    const_cast< bool& >(this->lb) = this->lbThread;
    return this->lb;
}

bool MouseEventListener::getRb(void) const {
    const_cast< bool& >(this->rb) = this->rbThread;
    return this->rb;
}

bool MouseEventListener::getMb(void) const {
    const_cast< bool& >(this->mb) = this->mbThread;
    return this->mb;
}

int MouseEventListener::getScroll(void) const {
    int ret = this->scroll;
    const_cast< int& >(this->scroll) = 0;
    return ret;
}

MouseEventListener::MouseEventListener(void) {
    this->coordinates = XY();
    this->scroll = 0;
    this->lb = false;
    this->lbThread = false;
    this->rb = false;
    this->rbThread = false;
    this->mb = false;
    this->mbThread = false;
    this->threadName = "MouseListener";
    this->threadGroup = "Listeners";
    this->params = std::vector< void* >();
    this->params.push_back(&this->lb);
    this->params.push_back(&this->lbThread);
    this->params.push_back(&this->rb);
    this->params.push_back(&this->rbThread);
    this->params.push_back(&this->mb);
    this->params.push_back(&this->mbThread);
    this->params.push_back(&this->scroll);
    this->params.push_back(&this->coordinates);
    this->interrupt = false;
    this->params.push_back(&this->interrupt);

    ThreadController::getInstance().createThread(this->threadName, this->threadGroup, &MouseEventListener::threadFunction, this->params);
}

void MouseEventListener::threadFunction(std::vector< void* >& params) {

    const DisplayController& dc = DisplayController::getInstance();
    Display* display = dc.getDisplay();
    XEvent xevent;
    Window window;

    memset(&xevent, 0, sizeof(xevent));

    window = DefaultRootWindow(display);
    XAllowEvents(display, AsyncBoth, CurrentTime);

    XGrabPointer(display,
                 window,
                 True,
                 PointerMotionMask | ButtonPressMask | ButtonReleaseMask ,
                 GrabModeAsync,
                 GrabModeAsync,
                 None,
                 None,
                 CurrentTime);

    while(!(*((bool*) params[8]))) {
        if (XPending(display) > 0 && !(*((bool*) params[8]))) {
            XNextEvent(display, &xevent);
        }

        switch (xevent.type) {
            XSendEvent(display, PointerWindow, True, 0xfff, &xevent);
            case MotionNotify:
                    ((XY*) params[7])->x = xevent.xmotion.x_root;
                    ((XY*) params[7])->y = xevent.xmotion.y_root;
                break;
            case ButtonPress:
                    switch (xevent.xbutton.button){
                        case Button1:
                            *((bool*) params[0]) = true;
                            *((bool*) params[1]) = true;
                            XUngrabPointer(display, CurrentTime);
                            MouseClicker::mouseDown(Button1);
                            XSync(display, true);
                            XGrabPointer(display,
                                window,
                                True,
                                PointerMotionMask | ButtonPressMask | ButtonReleaseMask ,
                                GrabModeAsync,
                                GrabModeAsync,
                                None,
                                None,
                                CurrentTime);
                        break;
                        case Button2:
                            *((bool*) params[2]) = true;
                            *((bool*) params[3]) = true;
                        break;
                        case Button3:
                            *((bool*) params[4]) = true;
                            *((bool*) params[5]) = true;
                        break;
                        case Button4:
                            ++*((int*) params[6]);
                        break;
                        case Button5:
                            --*((int*) params[6]);
                        break;
                    }
                break;
            case ButtonRelease:
                    switch (xevent.xbutton.button){
                        case Button1:
                            *((bool*) params[1]) = false;
                        break;
                        case Button2:
                            *((bool*) params[3]) = false;
                        break;
                        case Button3:
                            *((bool*) params[5]) = false;
                        break;
                    }
                break;
        }
    }

}
