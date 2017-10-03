#include "../../include/string"
#include "../../include/vector"
#include "../../include/algorithm"
#include "../../include/boost/lexical_cast.hpp"
#include "../ThreadController/ThreadController.h"
#include "PointerState.h"
#include "../Utils/Timer.cpp"
#include "DisplayController.h"
#include "MouseRecorder.h"
#include "MouseEventListener.h"

MouseRecorder::MouseRecorder(int threadClock) {
    MouseRecorder::instances++;
    MouseRecorder::recorders.push_back(this);
    this->threadName = MouseRecorder::threadGroup + boost::lexical_cast< std::string >(MouseRecorder::instances);
    this->params = std::vector< void* >();
    this->track = std::vector< PointerState >();
    this->threadClock = threadClock;
    this->threadMili = 1000 / threadClock;
    this->params.push_back(&this->threadMili);
    this->params.push_back(&this->track);
    this->running = false;
}

MouseRecorder::~MouseRecorder(void) {
    if (this->running) {
        this->end();
    }
    // Erase by value
    MouseRecorder::recorders.erase(
        std::remove(
            MouseRecorder::recorders.begin(),
            MouseRecorder::recorders.end(),
            this
        ),
        MouseRecorder::recorders.end()
    );
}

void MouseRecorder::start(void) {
    ThreadController::getInstance().createThread(
        this->threadName,
        this->threadGroup,
       &MouseRecorder::threadFunction,
        this->params
    );
    this->running = true;
}

void MouseRecorder::end(void) {
    if (this->running) {
        ThreadController::getInstance().closeThread(this->threadName);
        this->running = false;
    }
    delete &MouseEventListener::getInstance();
}

void MouseRecorder::endAll(void) {
    while (MouseRecorder::recorders.size() != 0) {
        MouseRecorder::recorders[0]->~MouseRecorder();
    }
}

std::vector< PointerState > MouseRecorder::getTrack(void) {
    return this->track;
}

int MouseRecorder::getClock(void) {
    return this->threadClock;
}

void MouseRecorder::threadFunction(std::vector< void* >& params) {
    Timer* timer = (Timer*) params[params.size() - 1];

    while (true) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(*((int*) params[0]) - timer->elapsed()));
        timer->reset();

        ((std::vector< PointerState >*) params[1])->push_back(PointerState());
    }
}

std::vector< MouseRecorder* > MouseRecorder::recorders = std::vector< MouseRecorder* >();
std::string MouseRecorder::threadGroup = "MouseRecorders";
int MouseRecorder::instances = 0;
