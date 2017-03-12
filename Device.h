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

#include <iostream>
#include <string>
using namespace std;

class Device {
public:
    Device(const string &a_name): name_{a_name}, process_queue_{new PCBQueue} {}

    // Returns true if process_queue_ is empty (Device has no requests), otherwise returns false.
    bool Is_Idle() { return process_queue_->empty(); }

    // Returns const reference to name_;
    const string &Get_Name() const { return name_; }

    // Add process to the back of the queue.
    void Add_Process(PCB *a_process) { process_queue_->enqueue(a_process); }

    // Remove and returns the process in the front of the queue.
    // Assumes queue is non-empty.
    PCB *Remove_Running_Process() { return process_queue_->dequeue(); }

    // Returns a const reference to the process in front of the queue.
    // Assumes queue is non-empty.
    const PCB *Running_Process() { return process_queue_->front(); }

    // Operator<< overload.
    friend ostream &operator<<(ostream &out, const Device &a_device);

protected:
    string name_;
    PCBQueue *process_queue_;
};

#endif
