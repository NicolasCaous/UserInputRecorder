#include "../include/iostream"
#include "../include/X11/Xlib.h"
#include "../include/unistd.h"
#include "MouseController/MouseRecorder.h"
#include "MouseController/MouseClicker.h"
#include "MouseController/DisplayController.h"
#include "MouseController/MousePlayer.h"
#include "MouseController/MouseEventListener.h"

int main(int argc, char ** argv) {

    sleep(1);
    //std::cout << "CLICKAND" << std::endl;
    //MouseClicker::mouseDown(1);
    //sleep(5);
    //MouseClicker::mouseUp(1);
    MouseRecorder mr = MouseRecorder(100);
    std::cout << "GRAVANDO" << std::endl;
    mr.start();
    sleep(5);
    mr.end();
    std::cout << "PAROU" << std::endl;
    MousePlayer mp = MousePlayer(mr.getTrack(), mr.getClock());
    mp.start();
    mp.join();
    std::cout << "ACABOU" << std::endl;

    return 0;
}
