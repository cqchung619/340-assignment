/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef DEVICE_H
#define DEVICE_H

#include "PCB.h"
#include "PCBQueue.h"

#include <queue>
#include <string>

class Device {
public:
    Device(const std::string &a_name): name_{a_name} {}

    // Returns const reference to name_;
    const std::string &Get_Name() { return name_; }

    // Add process to the back of the queue.
    void Add_Process(const PCB &a_process);

    // Remove process in the front of the queue.
    void Remove_Current_Process();

    // Returns a const reference to the process in front of the queue.
    const PCB &Current_Process();

    friend ostream &operator<<(ostream &out, const Device &a_device);

private:
    std::string name_;
    PCBQueue process_queue_;
};

#endif
