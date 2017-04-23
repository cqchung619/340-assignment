/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #2: Pre-Emptive SJF, Disk Scheduling and Accounting.
*/

#ifndef DEVICE_H
#define DEVICE_H

#include "PCB.h"
#include "PCBQueue.h"

#include <iostream>
#include <string>
using namespace std;

class Device {
public:
    Device(const string &a_name): name_{a_name} {}
    virtual ~Device() {}

    // Returns const reference to name_;
    const string &Get_Name() const { return name_; }

    // Returns true if process_queue_ is empty (Device has no requests), otherwise returns false.
    virtual bool Is_Idle() = 0;

    // Add process to the back of the queue.
    virtual void Add_Process(PCB *a_process) = 0;

    // Remove and returns the process in the front of the queue.
    // Assumes queue is non-empty.
    virtual PCB *Remove_Running_Process() = 0;

    // Returns a const reference to the process in front of the queue.
    // Assumes queue is non-empty.
    virtual const PCB *Running_Process() = 0;

    // Operator<< overload.
    friend ostream &operator<<(ostream &out, const Device &a_device);

protected:
    string name_;
};

#endif
