#include "ThreadController.h"
#include "../../include/stdexcept"
#include "../../include/iostream"
#include "../Utils/Timer.cpp"

ThreadController& ThreadController::getInstance(void) {
    static ThreadController instance;
    return instance;
}

ThreadController::~ThreadController(void) {
    std::map< std::string, boost::thread* >::iterator it;
    for (it = this->threads.begin(); it != this->threads.end(); it++) {
        it->second->interrupt();
        it->second->join();
        std::map< std::string, boost::thread_group* >::iterator it2;
        for (it2 = this->threadGroups.begin(); it2 != this->threadGroups.end(); it2++)
        {
            it2->second->remove_thread(it->second);
        }
        delete it->second;
    }
    this->threads.clear();
    std::map< std::string, boost::thread_group* >::iterator it2;
    for (it2 = this->threadGroups.begin(); it2 != this->threadGroups.end(); it2++) {
        delete it2->second;
    }
    this->threadGroups.clear();
}

void ThreadController::closeThread(std::string name) const {
    ThreadController* thisObject = const_cast< ThreadController* >(this);
    if (thisObject->threads.count(name) == 0) {
        throw std::invalid_argument( "Thread dont exist" );
    }
    boost::thread* thread = thisObject->threads[name];
    thread->interrupt();
    thread->join();
    std::map< std::string, boost::thread_group* >::iterator it;
    for (it = thisObject->threadGroups.begin(); it != thisObject->threadGroups.end(); it++) {
        it->second->remove_thread(thread);
    }
    thisObject->threads.erase(name);
    delete thread;
}

boost::thread* ThreadController::getThread(std::string name) const {
    ThreadController* thisObject = const_cast< ThreadController* >(this);
    if (thisObject->threads.count(name) == 0) {
        throw std::invalid_argument( "Thread dont exist" );
    }
    return thisObject->threads[name];
}

void ThreadController::createThread(
    std::string name,
    std::string group,
    void function(std::vector< void* >&),
    std::vector< void* >& params
) const {
    ThreadController* thisObject = const_cast< ThreadController* >(this);
    if (thisObject->threads.count(name) == 1) {
        throw std::invalid_argument( "Thread already initialized" );
    }

    if (thisObject->threadGroups.count(group) == 0) {
        thisObject->threadGroups[group] = new boost::thread_group;
    }
    Timer* timer = new Timer;
    params.push_back(timer);

    boost::thread* newThread = new boost::thread( function, boost::ref(params));
    thisObject->threads[name] = newThread;
    thisObject->threadGroups[group]->add_thread(newThread);
}

ThreadController::ThreadController(void) {
    this->threadGroups = std::map< std::string, boost::thread_group* >();
    this->threads = std::map< std::string, boost::thread* >();
}
