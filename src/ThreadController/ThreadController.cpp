#include "ThreadController.h"
#include "../../include/stdexcept"
#include "../../include/iostream"

ThreadController* ThreadController::get_instance(void)
{
    if (ThreadController::THREAD_CONTROLLER == NULL)
    {
        ThreadController::THREAD_CONTROLLER = new ThreadController;
    }
    return ThreadController::THREAD_CONTROLLER;
}

bool ThreadController::active(void)
{
    return (ThreadController::THREAD_CONTROLLER != NULL);
}

void ThreadController::print(std::string s)
{
    std::cout << s << std::endl;
}

void ThreadController::close_all_threads(void)
{
    std::map< std::string, boost::thread_group* >::iterator it;
    for (it = this->thread_groups->begin(); it != this->thread_groups->end(); it++)
    {
        it->second->interrupt_all();
        it->second->join_all();
        delete it->second;
    }
    this->thread_groups->clear();
    this->threads->clear();
    delete this->thread_groups;
    delete this->threads;
    ThreadController::THREAD_CONTROLLER = NULL;
    delete this;
}

void ThreadController::close_thread(std::string name)
{
    if (this->threads->count(name) == 0)
    {
        throw std::invalid_argument( "Thread dont exist" );
    }
    boost::thread* thread = (*this->threads)[name];
    thread->interrupt();
    thread->join();
    std::map< std::string, boost::thread_group* >::iterator it;
    for (it = this->thread_groups->begin(); it != this->thread_groups->end(); it++)
    {
        it->second->remove_thread(thread);
    }
    this->threads->erase(name);
    delete thread;
}

boost::thread* ThreadController::get_thread(std::string name)
{
    if (this->threads->count(name) == 0)
    {
        throw std::invalid_argument( "Thread dont exist" );
    }
    return (*this->threads)[name];
}

void ThreadController::create_thread(
    std::string name,
    std::string group,
    void function(std::vector< void* >&),
    std::vector< void* >& params
)
{

    if (this->threads->count(name) == 1)
    {
        throw std::invalid_argument( "Thread already initialized" );
    }

    if (this->thread_groups->count(group) == 0)
    {
        (*this->thread_groups)[group] = new boost::thread_group;
    }

    boost::thread* new_thread = new boost::thread( function, boost::ref(params));
    (*this->threads)[name] = new_thread;
    (*this->thread_groups)[group]->add_thread(new_thread);
}

ThreadController::ThreadController(void)
{
    this->thread_groups = new std::map< std::string, boost::thread_group* >;
    this->threads = new std::map< std::string, boost::thread* >;
}

ThreadController* ThreadController::THREAD_CONTROLLER;
