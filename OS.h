/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef OS_H
#define OS_H

#include "CPU.h"
#include "Device.h"
#include "InterruptHandler.h"
#include "Scheduler.h"

#include <algorithm>
#include <iostream>
using namespace std;

class OS {
public:
    OS(): PID_counter_{0} {}

    void Initialize_Devices(const vector<unsigned int> &number_of_devices);
    void Run();
private:
    bool running;
    unsigned int PID_counter_;

    InterruptHandler interrupt_handler_;
    Scheduler scheduler_;

    bool Is_Valid_Input(const string &an_input);
    void Handle_Input(const string &an_input);
};

#endif
