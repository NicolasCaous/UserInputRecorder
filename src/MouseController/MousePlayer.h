#include "../../include/string"
#include "../../include/vector"
#include "PointerState.h"

#ifndef MOUSEPLAYER_H
#define MOUSEPLAYER_H

class MousePlayer {
    public:
        MousePlayer(std::vector< PointerState > track, int threadClock);
        ~MousePlayer(void);
        void start(void);
        void end(void);
        void join(void);
        bool isRunning(void);
        static void endAll(void);
        std::vector< PointerState > getTrack(void);
        int getClock(void);
    private:
        static void threadFunction(std::vector< void* >& params);
        static std::vector< MousePlayer* > players;
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
