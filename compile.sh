#!/bin/bash

g++ -Wall src/MouseController/MouseTracker.cpp src/MouseController/MouseRecorder.cpp src/MouseController/MousePlayer.cpp src/MouseController/DisplayController.cpp -lX11 src/ThreadController/ThreadController.cpp -lboost_thread -lboost_system src/Utils/Timer.cpp src/Utils/XY.cpp src/main.cpp
