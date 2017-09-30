#include "../../include/cstddef"
#include "../../include/boost/thread.hpp"
#include "../../include/map"
#include "../../include/string"
#include "../../include/vector"

#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

class ThreadController {
    public:
        static ThreadController& getInstance(void);
        ~ThreadController(void);
        void closeThread(std::string name) const;
        boost::thread* getThread(std::string name) const;
        void createThread(std::string name, std::string group, void function(std::vector< void* >&), std::vector< void* >& params) const;
    private:
        ThreadController();
        ThreadController(const ThreadController&);
        ThreadController& operator= (const ThreadController&);
        std::map< std::string, boost::thread_group* > threadGroups;
        std::map< std::string, boost::thread* > threads;
    protected:
};

#endif
