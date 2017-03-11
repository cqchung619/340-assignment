/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef CPU_H
#define CPU_H

#include "PCB.h"

#include <iostream>
using namespace std;

class CPU {
public:
    CPU(): running_process_{nullptr} {}
    ~CPU() { delete running_process_; }

    // Add process to the back of the queue.
    void Bind_Process(PCB *a_process) { running_process_ = a_process; }

    // Remove and returns the process in the front of the queue.
    // Assumes queue is non-empty.
    PCB* Unbind_Process();

    // Returns a const reference to the process in front of the queue.
    // Assumes queue is non-empty.
    const PCB *Get_Running_Process() const { return running_process_; }

    // Operator<< overload.
    //friend ostream &operator<<(ostream &out, const CPU &a_CPU);

private:
    PCB *running_process_;
};

#endif
