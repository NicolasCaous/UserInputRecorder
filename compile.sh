#!/bin/bash

g++ -Wall src/MouseTracker.cpp -lX11 src/ThreadController/ThreadController.cpp -lboost_thread -lboost_system src/Utils/XY.cpp src/main.cpp
