/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef OS_H
#define OS_H

#include "InterruptHandler.h"
#include "Scheduler.h"

#include <iostream>
using namespace std;

class OS {
public:
    void Run();
private:
    bool running;
    InterruptHandler interrupt_handler_;
    Scheduler scheduler_;
};

#endif
