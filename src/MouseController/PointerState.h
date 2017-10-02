#ifndef POINTERSTATE_H
#define POINTERSTATE_H

#include "../Utils/XY.h"

class PointerState {
    public:
        PointerState(void);
        XY xy;
        bool lb;
        bool rb;
        bool mb;
        int scroll;
};

#endif
