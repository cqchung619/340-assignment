/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #3: Paging, Memory Management
*/

#ifndef DISK_H
#define DISK_H

#include "Device.h"
#include "DiskQueue.h"
#include "PCB.h"

class Disk: public Device {
public:
    Disk(const string &a_name, const unsigned int n):
    Device::Device{a_name}, CYLINDER_COUNT{n}, process_queue_{new DiskQueue} {}

    virtual ~Disk() {}

    const unsigned int  Get_Cylinder_Count() const { return CYLINDER_COUNT; }

    // Returns true if process_queue_ is empty (Device has no requests), otherwise returns false.
    bool Is_Idle() { return process_queue_->empty(); }

    // Add process to the back of the queue.
    void Add_Process(PCB *a_process) { process_queue_->enqueue(a_process); }

    // Remove and returns the process in the front of the queue.
    // Assumes queue is non-empty.
    PCB *Remove_Running_Process() { return process_queue_->dequeue(); }

    // Returns a const reference to the process in front of the queue.
    // Assumes queue is non-empty.
    const PCB *Running_Process() { return process_queue_->front(); }

    // Operator<< overload.
    friend ostream &operator<<(ostream &out, const Disk &a_disk);

private:
    const unsigned int CYLINDER_COUNT;
    DiskQueue *process_queue_;
};

#endif
