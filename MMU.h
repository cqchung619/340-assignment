/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #3: Paging, Memory Management
*/

#ifndef MMU_H
#define MMU_H

#include "PCB.h"

#include <iostream>
#include <map>
#include <set>
using namespace std;

class MMU {
public:
    MMU(const unsigned int mem, const unsigned int proc_mem, const unsigned int page_size):
        MEM_MAX_{mem},
        PROC_MEM_MAX_{proc_mem},
        PAGE_SIZE_MAX_{page_size} {

        unsigned int number_of_frames = MEM_MAX_ / PAGE_SIZE_MAX_;
        for (unsigned int i = 0; i < number_of_frames; ++i) {
            free_frame_list_.insert(i);
        }
    }
    ~MMU() {}

    // Accessors.
    const unsigned int Get_MEM_MAX() { return MEM_MAX_; }
    const unsigned int Get_PROC_MEM_MAX() { return PROC_MEM_MAX_; }
    const unsigned int Get_PAGE_SIZE_MAX() { return PAGE_SIZE_MAX_; }


    void Allocate_Mem(PCB *a_process);
    void Deallocate_Mem(PCB *a_process);

private:
    const unsigned int MEM_MAX_;
    const unsigned int PROC_MEM_MAX_;
    const unsigned int PAGE_SIZE_MAX_;

    set<unsigned int> free_frame_list_;
    map<unsigned int, unsigned int> frame_table_;
};

#endif
