/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #3: Paging, Memory Management
*/

#ifndef PCB_QUEUE_H
#define PCB_QUEUE_H

#include "PCB.h"

#include <iostream>
#include <list>
using namespace std;

class PCBQueue {
public:
    // Destructor
    virtual ~PCBQueue() {
        for (auto process : process_list_) {
            delete process;
        }
    }

    // Returns true if queue is empty, otherwise returns false.
    bool empty() const { return process_list_.empty(); }

    // Returns number of PCBs in queue.
    size_t size() const { return process_list_.size(); }

    // Adds process to the back of the queue.
    virtual void enqueue(PCB *a_process) { process_list_.push_back(a_process); }

    // Removes the process in front of the queue and returns a copy.
    // Assumes queue is non-empty.
    virtual PCB *dequeue();

    // Returns a reference to the process in the front of the queue.
    // Assumes queue is non-empty.
    PCB *front();

    // Returns a reference to the process in the back of the queue.
    // Assumes queue is non-empty.
    PCB *back();

    // Outputs the process_list_ to out in the specified format.
    void Output_Processes(ostream &out, PCB::OutputFormat format) const;

protected:
    list<PCB*> process_list_;
};

#endif
