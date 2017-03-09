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
using namespace std;

class Device {
public:
    Device(const string &a_name): name_{a_name} {}

    /*
     * Returns const reference to name_;
     */
    const string &Get_Name() { return name_; }

    /*
     * Add process to the back of the queue.
     */
    void Add_Process(const PCB &a_process) { process_queue_.enqueue(a_process); }

    /*
     * Remove and returns the process in the front of the queue.
     * Assumes queue is non-empty.
     */
    PCB Remove_Current_Process() { return process_queue_.dequeue(); }

    /*
     * Returns a const reference to the process in front of the queue.
     * Assumes queue is non-empty.
     */
    const PCB &Current_Process() { return process_queue_.front(); }

    /*
     * Operator<< overload.
     */
    friend ostream &operator<<(ostream &out, const Device &a_device);

private:
    string name_;
    PCBQueue process_queue_;
};

#endif
