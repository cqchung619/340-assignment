#ifndef JOB_POOL_H
#define JOB_POOL_H

#include "PCB.h"

#include <iostream>
#include <list>
#include <map>
using namespace std;

class JobPool {
public:
    JobPool() {}
    ~JobPool() {
        for (auto item : pool_) {
            for (auto process : item.second) {
                delete process;
            }
        }
    }

    PCB *Find_Largest_Process(const unsigned int size_limit);
    void Add_Process(PCB *a_process);
    void Remove_Pocess(PCB *a_process);

    void Output_Job_Pool(ostream& out);
private:
    map<unsigned int, list<PCB*>> pool_;


};

#endif
