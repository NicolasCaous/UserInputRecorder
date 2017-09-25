#include "../include/iostream"
#include "../include/unistd.h"
#include "../include/map"
#include "../include/string"
#include "../include/vector"
#include "../include/exception"
#include "../include/boost/chrono.hpp"
#include "../include/boost/thread/thread.hpp"
#include "../include/X11/Xlib.h"
#include "./Utils/Timer.cpp"
#include "./Utils/XY.h"
#include "MouseTracker.h"
#include "ThreadController/ThreadController.h"

std::vector< XY > track;

void gravar(std::vector< void* >& params)
{
    Timer* timer = (Timer*) params[params.size() - 1];
    MouseTracker* mt1 = MouseTracker::get_instance();
    XY anterior;
    while (true)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(*((int*) params[0]) - timer->elapsed()));
        timer->reset();
        XY now;
            now.x = mt1->get_coordinates().x;
            now.y = mt1->get_coordinates().y;
        /*if (track.size() == 0)
        {
            anterior.x = now.x;
            anterior.y = now.y;

            track.push_back(anterior);
        }
        else
        {
            anterior.x = now.x - anterior.x;
            anterior.y = now.y - anterior.y;

            track.push_back(anterior);

            anterior.x = now.x;
            anterior.y = now.y;
        }*/ track.push_back(now);
    }
}

void reproduzir(std::vector< void* >& params)
{
    Timer* timer = (Timer*) params[params.size() - 1];
    int i = 0;
    Display *d = XOpenDisplay(0);
    Window root_window;
    root_window = XRootWindow(d, 0);

    MouseTracker* mt = MouseTracker::get_instance();

    /*XWarpPointer(
                d, None, root_window,
                0, 0, 0, 0,
                -1920, -1920
            );
    XFlush(d);*/

    while (true)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(*((int*) params[0]) - timer->elapsed()));
        timer->reset();

        if (d) {
            //XY cood = mt->get_coordinates();
            XWarpPointer(
                d, None, root_window,
                0, 0, 0, 0,
                track[i].x, track[i].y
            );
            XFlush(d);
        }
        ++i;
    }

    XCloseDisplay(d);

}

int main(int argc, char ** argv) {

    std::vector< void* > params;
    int x = 20;
    params.push_back(&x);
    ThreadController* tc = ThreadController::get_instance();

    sleep(1);
    tc->create_thread("1", "num", &gravar, params);
    sleep(5);
    tc->close_thread("1");
    tc->create_thread("2", "num", &reproduzir, params);
    sleep(5);
    tc->close_thread("2");
    sleep(5);
    tc->close_all_threads();
    std::cout << ((Timer*) params[params.size()-1])->elapsed() << std::endl;

    return 0;
}
