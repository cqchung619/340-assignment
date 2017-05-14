#ifndef JOB_POOL_H
#define JOB_POOL_H

#include "PCB.h"
#include "PCBQueue.h"

#include <map>

class JobPool {
public:
    JobPool() {}
    ~JobPool() {
        for (auto item : pool_) {
            delete item.second;
        }
    }

    PCB *Find_Largest_Process(const unsigned int size_limit);
    void Add_Process(PCB *a_process);
    void Remove_Pocess(PCB *a_process);

    void Output_Job_Pool();
private:
    map<unsigned int, PCBQueue*> pool_;

    
};

#endif
