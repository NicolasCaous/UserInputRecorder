#include "PointerState.h"
#include "MouseEventListener.h"

PointerState::PointerState(void) {
    const MouseEventListener& mel = MouseEventListener::getInstance();
    this->xy = mel.getCoordinates();
    this->lb = mel.getLb();
    this->rb = mel.getRb();
    this->mb = mel.getMb();
    this->scroll = mel.getScroll();
}

