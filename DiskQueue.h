/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #3: Paging, Memory Management

The DiskQueue is a circular linked list that simulates the CLOOK disk scheduling algorithm. Each process is scheduled in
ascending order based on the cylinder accessed. The seek head is always traveling inwards (i.e. higher cylinder number).
When there is no job towards the inner cylinders, the seek head circles back to the first job on the outer edge. In the
circular linked list, the last job points to the first job of the outer edge, so seek head progression is simple and
just keeps moving foward.

Jobs accessing the same cylinder is scheduled as FCFS(First Come First Serve). The new job goes after the last job
accessing the same cylinder. The exception is if the current seek head is at that cynlinder and the next job is not
accessing the same cylinder. In this case, the job goes behind the seek head. In the circular queue, this means that the
job is inserted before the seek head position.
*/

#ifndef DISK_QUEUE_H
#define DISK_QUEUE_H

#include "PCB.h"

#include <iostream>
using namespace std;

class DiskQueue {
public:
    DiskQueue(): queue_head_{nullptr}, queue_tail_{nullptr}, seek_head_{nullptr}, current_size_{0} {}
    ~DiskQueue() {}

    // Returns true if queue is empty, otherwise returns false.
    bool empty() const { return current_size_ == 0; }

    // Returns number of PCBs in queue.
    size_t size() const { return current_size_; }

    // Adds process to the back of the queue.
    void enqueue(PCB *a_process);

    // Removes the process in front of the queue and returns a copy.
    // Assumes queue is non-empty.
    PCB *dequeue();

    PCB *remove(const unsigned int pid);

    // Returns a reference to the process in the front of the queue.
    // Assumes queue is non-empty.
    PCB *front();

    // Returns a reference to the process in the back of the queue.
    // Assumes queue is non-empty.
    PCB *back();

    // Outputs the process_list_ to out in the specified format.
    void Output_Processes(ostream &out, PCB::OutputFormat format) const;

private:
    struct Node {
        PCB *process;
        unsigned int cylinder_accessed;
        Node *next;

        Node(PCB *a_process): process{a_process} {
            cylinder_accessed = (unsigned int) stoi(process->Get_Parameter(4));
            next = nullptr;
        }
    };

    Node *queue_head_;
    Node *queue_tail_;
    Node *seek_head_;
    size_t current_size_;
};

#endif
