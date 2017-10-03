#!/bin/bash

g++ -Wall src/MouseController/MouseEventListener.cpp src/MouseController/MouseRecorder.cpp src/MouseController/MousePlayer.cpp src/MouseController/MouseClicker.cpp -lXtst -lX11 -lm src/MouseController/MouseMover.cpp src/MouseController/DisplayController.cpp -lX11 src/ThreadController/ThreadController.cpp -lboost_thread -lboost_system src/Utils/Timer.cpp src/Utils/XY.cpp src/MouseController/PointerState.cpp src/main.cpp
