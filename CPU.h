/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef CPU_H
#define CPU_H

#include "PCB.h"
#include "PCBQueue.h"

#include <iostream>
using namespace std;

class CPU {
public:
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
    friend ostream &operator<<(ostream &out, const CPU &a_CPU);

private:
    PCBQueue process_queue_;
};

#endif
