#include "../../include/cstddef"
#include "../../include/boost/thread.hpp"
#include "../../include/map"
#include "../../include/string"
#include "../../include/vector"

#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

class ThreadController {
    public:
        static ThreadController* getInstance(void);
        static bool active(void);
        static void print(std::string obj);
        void closeAllThreads(void);
        void closeThread(std::string name);
        boost::thread* getThread(std::string name);
        void createThread(std::string name, std::string group, void function(std::vector< void* >&), std::vector< void* >& params);
    private:
        ThreadController(void);
        static ThreadController* THREAD_CONTROLLER;
        std::map< std::string, boost::thread_group* >* threadGroups;
        std::map< std::string, boost::thread* >* threads;
    protected:
};

#endif
