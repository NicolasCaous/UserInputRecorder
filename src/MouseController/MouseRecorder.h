#include "../../include/string"
#include "../../include/vector"

#ifndef MOUSERECORDER_H
#define MOUSERECORDER_H

class MouseRecorder {
    public:
        MouseRecorder(void);
        ~MouseRecorder(void);
        void start(void);
        void end(void);
        static void endAll(void);
        std::vector< XY > getTrack(void);
    private:
        static void threadFunction(std::vector< void* >& params);
        static std::vector< MouseRecorder* > recorders;
        static std::string threadGroup;
        std::string threadName;
        std::vector< void* > params;
        std::vector< XY > track;
        static const int THREAD_CLOCK;
        int threadMili;
        bool running;
    protected:
};

#endif
