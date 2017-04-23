/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #2: Pre-Emptive SJF, Disk Scheduling and Accounting

A representation of a disk device. This class uses a circular linked list to implement a disk queue.

The circular linked list simulates the CLOOK disk scheduling algorithm. Each process is scheduled in
ascending order based on the cylinder accessed. The seek head is always traveling inwards
(i.e. higher cylinder number). When there is no job towards the inner cylinders, the seek head circles
back to the first job on the outer edge. In the circular linked list, the last job points to the first
job of the outer edge, so seek head progression is simple and just keeps moving foward.

Jobs accessing the same cylinder is scheduled as FCFS(First Come First Serve). The new job goes after
the last job accessing the same cylinder. The exception is if the current seek head is at that cynlinder
and the next job is not accessing the saem cylinder. In this case, the job goes behind the seek head. In
the circular queue, this means that the job is inserted before the seek head position.


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
