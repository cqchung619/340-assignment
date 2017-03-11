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
#include "PCB.h"
#include "PCBQueue.h"
#include "Scheduler.h"

#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

class OS {
public:
    OS(): PID_counter_{0} {}

    void Initialize_Devices(const vector<unsigned int> &device_count);
    void Run();
private:
    bool running;
    unsigned int PID_counter_;
    map<string, Device> device_table_;
    PCBQueue ready_queue_;


    bool Is_Valid_Input(const string &an_input);
    void Handle_Input(const string &an_input);

};

#endif
