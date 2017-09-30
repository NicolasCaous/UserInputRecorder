#include "../../include/string"
#include "../../include/vector"
#include "../../include/algorithm"
#include "../../include/boost/lexical_cast.hpp"
#include "../ThreadController/ThreadController.h"
#include "../Utils/XY.h"
#include "../Utils/Timer.cpp"
#include "DisplayController.h"
#include "MousePlayer.h"
#include "MouseTracker.h"

MousePlayer::MousePlayer(std::vector< XY > track, int threadClock) {
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

std::vector< XY > MousePlayer::getTrack(void) {
    return this->track;
}

int MousePlayer::getClock(void) {
    return this->threadClock;
}

void MousePlayer::threadFunction(std::vector< void* >& params) {
    Timer* timer = (Timer*) params[params.size() - 1];
    Window root_window;
    root_window = XRootWindow(DisplayController::getInstance().getDisplay(), 0);
    std::vector< XY > vetor = *((std::vector< XY >*) params[1]);

    unsigned int i=0;
    while (i < vetor.size()) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(*((int*) params[0]) - timer->elapsed()));
        timer->reset();

        XWarpPointer(
            DisplayController::getInstance().getDisplay(), None, root_window,
            0, 0, 0, 0,
            vetor[i].x, vetor[i].y
        );
        DisplayController::getInstance().flush();
        ++i;
    }

    *((bool*) params[2]) = false;
}

std::vector< MousePlayer* > MousePlayer::players = std::vector< MousePlayer* >();
std::string MousePlayer::threadGroup = "MousePlayers";
int MousePlayer::instances = 0;
