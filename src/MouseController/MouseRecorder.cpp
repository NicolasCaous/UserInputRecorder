#include "../../include/iostream"
#include "../../include/string"
#include "../../include/vector"
#include "../../include/algorithm"
#include "../../include/boost/lexical_cast.hpp"
#include "../ThreadController/ThreadController.h"
#include "../Utils/XY.h"
#include "../Utils/Timer.cpp"
#include "DisplayController.h"
#include "MouseRecorder.h"
#include "MouseTracker.h"

MouseRecorder::MouseRecorder(void) {
    MouseRecorder::recorders.push_back(this);
    this->threadName = MouseRecorder::threadGroup + boost::lexical_cast< std::string >(MouseRecorder::recorders.size());
    this->params = std::vector< void* >();
    this->track = std::vector< XY >();
    this->threadMili = 1000 / MouseRecorder::THREAD_CLOCK;
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
    ThreadController::getInstance().closeThread(this->threadName);
    this->running = false;
}

void MouseRecorder::endAll(void) {
    while (MouseRecorder::recorders.size() != 0) {
        MouseRecorder::recorders[0]->~MouseRecorder();
    }
}

std::vector< XY > MouseRecorder::getTrack(void) {
    return this->track;
}

void MouseRecorder::threadFunction(std::vector< void* >& params) {
    Timer* timer = (Timer*) params[params.size() - 1];
    const MouseTracker& mt = MouseTracker::getInstance();

    while (true) {
        std::cout << "GRANVANDO" << std::endl;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(*((int*) params[0]) - timer->elapsed()));
        timer->reset();

        ((std::vector< XY >*) params[1])->push_back(mt.getCoordinates());
    }
}

std::vector< MouseRecorder* > MouseRecorder::recorders = std::vector< MouseRecorder* >();
std::string MouseRecorder::threadGroup = "MouseRecorders";
const int MouseRecorder::THREAD_CLOCK = 100;
