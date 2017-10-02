#include "../../include/string"
#include "../../include/vector"
#include "../../include/algorithm"
#include "../../include/boost/lexical_cast.hpp"
#include "../ThreadController/ThreadController.h"
#include "PointerState.h"
#include "../Utils/Timer.cpp"
#include "DisplayController.h"
#include "MouseEventListener.h"
#include "MousePlayer.h"
#include "MouseClicker.h"

MousePlayer::MousePlayer(std::vector< PointerState > track, int threadClock) {
    MousePlayer::instances++;
    MousePlayer::players.push_back(this);
    this->threadName = MousePlayer::threadGroup + boost::lexical_cast< std::string >(MousePlayer::instances);
    this->params = std::vector< void* >();
    this->track = track;
    this->threadClock = threadClock;
    this->threadMili = 1000 / threadClock;
    this->running = false;
    this->params.push_back(&this->threadMili);
    this->params.push_back(&this->track);
    this->params.push_back(&this->running);
}

MousePlayer::~MousePlayer(void) {
    if (this->running) {
        this->end();
    }
    // Erase by value
    MousePlayer::players.erase(
        std::remove(
            MousePlayer::players.begin(),
            MousePlayer::players.end(),
            this
        ),
        MousePlayer::players.end()
    );
}

void MousePlayer::start(void) {
    delete &MouseEventListener::getInstance();
    ThreadController::getInstance().createThread(
        this->threadName,
        this->threadGroup,
       &MousePlayer::threadFunction,
        this->params
    );
    this->running = true;
}

void MousePlayer::end(void) {
    if (this->running) {
        ThreadController::getInstance().closeThread(this->threadName);
        this->running = false;
    }
}

void MousePlayer::join(void) {
    if (this->running) {
        ThreadController::getInstance().getThread(this->threadName)->join();
    }
}

bool MousePlayer::isRunning(void) {
    return this->running;
}

void MousePlayer::endAll(void) {
    while (MousePlayer::players.size() != 0) {
        MousePlayer::players[0]->~MousePlayer();
    }
}

std::vector< PointerState > MousePlayer::getTrack(void) {
    return this->track;
}

int MousePlayer::getClock(void) {
    return this->threadClock;
}

void MousePlayer::threadFunction(std::vector< void* >& params) {
    Timer* timer = (Timer*) params[params.size() - 1];
    Window root_window;
    root_window = XRootWindow(DisplayController::getInstance().getDisplay(), 0);
    std::vector< PointerState >& vetor = *((std::vector< PointerState >*) params[1]);

    bool lb = false;
    bool rb = false;
    bool mb = false;
    unsigned int i=0;
    while (i < vetor.size()) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(*((int*) params[0]) - timer->elapsed()));
        timer->reset();

        XWarpPointer(
            DisplayController::getInstance().getDisplay(), None, root_window,
            0, 0, 0, 0,
            vetor[i].xy.x, vetor[i].xy.y
        );
        if (vetor[i].lb != lb) {
            lb = vetor[i].lb;
            if (lb) {
                MouseClicker::mouseDown(Button1);
            } else {
                MouseClicker::mouseUp(Button1);
            }
        }
        if (vetor[i].rb != rb) {
            rb = vetor[i].rb;
            if (rb) {
                MouseClicker::mouseDown(Button2);
            } else {
                MouseClicker::mouseUp(Button2);
            }
        }
        if (vetor[i].mb != mb) {
            mb = vetor[i].mb;
            if (mb) {
                MouseClicker::mouseDown(Button3);
            } else {
                MouseClicker::mouseUp(Button3);
            }
        }
        DisplayController::getInstance().flush();
        ++i;
    }

    *((bool*) params[2]) = false;
}

std::vector< MousePlayer* > MousePlayer::players = std::vector< MousePlayer* >();
std::string MousePlayer::threadGroup = "MousePlayers";
int MousePlayer::instances = 0;
