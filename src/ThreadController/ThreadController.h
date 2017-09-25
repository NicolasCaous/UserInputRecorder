#include "../../include/cstddef"
#include "../../include/boost/thread.hpp"
#include "../../include/map"
#include "../../include/string"
#include "../../include/vector"

#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

class ThreadController
{
    public:
        static ThreadController* get_instance(void);
        static bool active(void);
        static void print(std::string obj);
        void close_all_threads(void);
        void close_thread(std::string name);
        boost::thread* get_thread(std::string name);
        void create_thread(std::string name, std::string group, void function(std::vector< void* >&), std::vector< void* >& params);
    private:
        ThreadController(void);
        static ThreadController* THREAD_CONTROLLER;
        std::map< std::string, boost::thread_group* >* thread_groups;
        std::map< std::string, boost::thread* >* threads;
    protected:
};

#endif
