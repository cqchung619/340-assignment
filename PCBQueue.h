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

    bool empty() { return process_list_.empty(); }
    size_t size() { return process_list_.size(); }

    void enqueue(PCB *&a_process) { process_list_.push_back(a_process); }
    PCB *dequeue();

    PCB *front() { return process_list_.front(); }
    PCB *back() { return process_list_.back(); }

    friend ostream &operator<<(ostream &out, const PCBQueue &a_PCB_Queue);

private:
    list<PCB*> process_list_;
};

#endif
