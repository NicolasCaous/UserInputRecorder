#include "../include/iostream"
#include "../include/unistd.h"
#include "../include/map"
#include "../include/string"
#include "../include/vector"
#include "../include/exception"
#include "../include/boost/chrono.hpp"
#include "../include/boost/thread/thread.hpp"
#include "MouseTracker.h"
#include "ThreadController/ThreadController.h"

void funcao(std::vector< void* >& params)
{
    while (true)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(*((int*) params[0])));
        MouseTracker* mt1 = MouseTracker::get_instance();
        MouseTracker* mt2 = MouseTracker::get_instance();

        std::cout << ThreadController::active() << std::endl;
        std::cout << mt1->get_coordinates().x << std::endl;
        std::cout << mt2->get_coordinates().y << std::endl;
    }
}

int main(int argc, char ** argv) {

    std::vector< void* > params;
    int x = 2;
    params.push_back(&x);
    ThreadController* tc = ThreadController::get_instance();

    tc->create_thread("1", "num", &funcao, params);
    sleep(2);
    tc->close_all_threads();
    std::cout << ThreadController::active() << std::endl;

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
