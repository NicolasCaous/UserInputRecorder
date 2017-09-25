#include "./Utils/XY.h"

#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H

class MouseTracker
{
    public:
        static MouseTracker* get_instance(void);
        XY get_coordinates(void);
    private:
        void update(void);
        MouseTracker(void);
        static MouseTracker* tracker;
        XY coordinates;
    protected:
};

#endif
