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
    for (it = this->threads->begin(); it != this->threads->end(); it++) {
        it->second->interrupt();
        it->second->join();
        std::map< std::string, boost::thread_group* >::iterator it2;
        for (it2 = this->threadGroups->begin(); it2 != this->threadGroups->end(); it2++)
        {
            it2->second->remove_thread(it->second);
        }
        delete it->second;
    }
    this->threads->clear();
    std::map< std::string, boost::thread_group* >::iterator it2;
    for (it2 = this->threadGroups->begin(); it2 != this->threadGroups->end(); it2++) {
        delete it2->second;
    }
    this->threadGroups->clear();
    delete this->threadGroups;
    delete this->threads;
}

void ThreadController::closeThread(std::string name) const {
    if (this->threads->count(name) == 0) {
        throw std::invalid_argument( "Thread dont exist" );
    }
    boost::thread* thread = (*this->threads)[name];
    thread->interrupt();
    thread->join();
    std::map< std::string, boost::thread_group* >::iterator it;
    for (it = this->threadGroups->begin(); it != this->threadGroups->end(); it++) {
        it->second->remove_thread(thread);
    }
    this->threads->erase(name);
    delete thread;
}

boost::thread* ThreadController::getThread(std::string name) const {
    if (this->threads->count(name) == 0) {
        throw std::invalid_argument( "Thread dont exist" );
    }
    return (*this->threads)[name];
}

void ThreadController::createThread(
    std::string name,
    std::string group,
    void function(std::vector< void* >&),
    std::vector< void* >& params
) const {
    if (this->threads->count(name) == 1) {
        throw std::invalid_argument( "Thread already initialized" );
    }

    if (this->threadGroups->count(group) == 0) {
        (*this->threadGroups)[group] = new boost::thread_group;
    }
    Timer* timer = new Timer;
    params.push_back(timer);

    boost::thread* newThread = new boost::thread( function, boost::ref(params));
    (*this->threads)[name] = newThread;
    (*this->threadGroups)[group]->add_thread(newThread);
}

ThreadController::ThreadController(void) {
    this->threadGroups = new std::map< std::string, boost::thread_group* >;
    this->threads = new std::map< std::string, boost::thread* >;
}
