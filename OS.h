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
#include "PCB.h"
#include "PCBQueue.h"
#include "Scheduler.h"

#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

class OS {
public:
    OS(): running_{true}, PID_counter_{0}, cpu_{new CPU}, ready_queue_{new PCBQueue} {}
    ~OS() {
        delete cpu_;
        delete ready_queue_;
        for (auto item : device_table_) {
            delete item.second;
        }
    }

    // @device_count: Holds the number of each devie to be created.
    //                Order of the numbers is printer, disk, CD/RW.
    void Initialize_Devices(const vector<unsigned int> &device_count);

    void Run();

private:
    bool running_;
    unsigned int PID_counter_;
    CPU *cpu_;
    PCBQueue* ready_queue_;
    map<string, Device*> device_table_;

    // Input validator for interrupts and system calls.
    // Valid only if length 1 or 2.
    // Length 1: A, S, t
    // Length 2: (p/c/d)#, (P/C/D)#
    bool Is_Valid_Signal_Input(const string &an_input);

    // Processes the input to determine if the Interrupr Handler or the System Call Handler should be used.
    void Process_Input(const string &an_input);

    // Interrupr Handler function.
    void Handle_Interrupt(const string &an_input);

    // System Call Handler function.
    void Handle_Sys_Call(const string &an_input);

    void test();
};

#endif
