#include "../include/iostream"
#include "../include/unistd.h"
#include "MouseController/MouseRecorder.h"
#include "MouseController/MousePlayer.h"

int main(int argc, char ** argv) {

    sleep(1);
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
