#include "./utils/XY.h"

#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H

class MouseTracker
{
    public:
        static MouseTracker* getInstance(void);
        XY getCoordinates(void);
    private:
        void update(void);
        MouseTracker(void);
        static MouseTracker* tracker;
        XY coordinates;
    protected:
};

#endif
