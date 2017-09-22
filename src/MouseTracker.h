#include "./utils/XY.h"

#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H

class MouseTracker
{
    public:
        static MouseTracker* getInstance(void);
        XY getCoordinates(void);
        void update(void);
    private:
        MouseTracker(void);
        static MouseTracker* tracker;
        XY coordinates;
    protected:
};

#endif
