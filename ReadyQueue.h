#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include "PCBQueue.h"

class ReadyQueue: public PCBQueue {
public:
    // SJF Scheduling.
    virtual void enqueue(PCB *a_process);
};

#endif
