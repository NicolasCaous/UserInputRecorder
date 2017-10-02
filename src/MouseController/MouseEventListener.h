#include "../Utils/XY.h"
#include "../../include/string"
#include "../../include/vector"

#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

class MouseEventListener {
    public:
        static MouseEventListener& getInstance(void);
        ~MouseEventListener(void);
        XY getCoordinates(void) const;
        bool getLb(void) const;
        bool getRb(void) const;
        bool getMb(void) const;
        int getScroll(void) const;
    private:
        MouseEventListener(void);
        MouseEventListener(const MouseEventListener&);
        MouseEventListener& operator= (const MouseEventListener&);
        static void threadFunction(std::vector< void* >& params);
        XY coordinates;
        bool lbThread;
        bool lb;
        bool rbThread;
        bool rb;
        bool mbThread;
        bool mb;
        int scroll;
        std::vector< void* > params;
        std::string threadName;
        std::string threadGroup;
        bool interrupt;
    protected:
};

#endif
