/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #2: Pre-Emptive SJF, Disk Scheduling and Accounting
*/

#ifndef CD_H
#define CD_H

#include "Device.h"
#include "PCBQueue.h"

class CD: public Device {
public:
    CD(const string &a_name): Device::Device{a_name}, process_queue_{new PCBQueue} {}
    virtual ~CD() {}

    // Returns true if process_queue_ is empty (Device has no requests), otherwise returns false.
    virtual bool Is_Idle() { return process_queue_->empty(); }

    // Add process to the back of the queue.
    virtual void Add_Process(PCB *a_process) { process_queue_->enqueue(a_process); }

    // Remove and returns the process in the front of the queue.
    // Assumes queue is non-empty.
    virtual PCB *Remove_Running_Process() { return process_queue_->dequeue(); }

    // Returns a const reference to the process in front of the queue.
    // Assumes queue is non-empty.
    virtual const PCB *Running_Process() { return process_queue_->front(); }

    // Operator<< overload.
    friend ostream &operator<<(ostream &out, const CD &a_cd);

private:
    PCBQueue *process_queue_;
};

#endif
