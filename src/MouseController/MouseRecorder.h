#include "../../include/string"
#include "../../include/vector"
#include "PointerState.h"

#ifndef MOUSERECORDER_H
#define MOUSERECORDER_H

class MouseRecorder {
    public:
        MouseRecorder(int threadClock);
        ~MouseRecorder(void);
        void start(void);
        void end(void);
        static void endAll(void);
        std::vector< PointerState > getTrack(void);
        int getClock(void);
    private:
        static void threadFunction(std::vector< void* >& params);
        static std::vector< MouseRecorder* > recorders;
        static std::string threadGroup;
        static int instances;
        std::string threadName;
        std::vector< void* > params;
        std::vector< PointerState > track;
        int threadMili;
        int threadClock;
        bool running;
    protected:
};

#endif
