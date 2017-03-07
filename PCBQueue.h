/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef PCB_QUEUE_H
#define PCB_QUEUE_H

#include "PCB.h"

#include <iostream>
#include <list>
using namespace std;

class PCBQueue {
public:

    ~PCBQueue() {
        for (PCB *process : process_list_) {
            delete process;
        }
        process_list_.clear();
    }

    /*
     * Returns true if queue is empty, otherwise returns false.
     */
    bool empty() { return process_list_.empty(); }

    /*
     * Returns number of PCBs in queue.
     */
    size_t size() { return process_list_.size(); }

    /*
     * Adds process to the back of the queue.
     */
    void enqueue(PCB *&a_process) { process_list_.push_back(a_process); }

    /*
     * Removes and returns the process in front of the queue.
     * If queue is empty, returns a nullptr.
     */
    PCB *dequeue();

    /*
     * Returns the process in the front of the queue.
     * If queue is empty, returns a nullptr.
     */
    PCB *front() { return (empty() ? nullptr : process_list_.front()); }

    /*
     * Returns the process in the back of the queue.
     * If queue is empty, returns a nullptr.
     */
    PCB *back() { return (empty() ? nullptr : process_list_.back()); }

    /*
     * Operator<< overload.
     */
    friend ostream &operator<<(ostream &out, const PCBQueue &a_PCB_Queue);

private:
    list<PCB*> process_list_;
};

#endif
