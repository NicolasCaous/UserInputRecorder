#include "../Utils/XY.h"

#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H

class MouseTracker {
    public:
        static MouseTracker& getInstance(void);
        ~MouseTracker(void);
        XY getCoordinates(void) const;
    private:
        MouseTracker() {}
        MouseTracker(const MouseTracker&);
        MouseTracker& operator= (const MouseTracker&);
        void update(void);
        XY coordinates;
    protected:
};

#endif
