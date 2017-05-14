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
    MMU() {}
    ~MMU() {}

    unsigned int Available_Mem_Size() { return free_frame_list_.size(); }

    // Accessors and Modifiers.
    void Set_Mem_Max(const unsigned int mem) { mem_max_ = mem; }
    void Set_Proc_Mem_Max(const unsigned int proc_mem) { proc_mem_max_ = proc_mem; }
    void Set_Page_Size_Max(const unsigned int page_size) { page_size_max_ = page_size; }

    unsigned int Get_Mem_Max() const { return mem_max_; }
    unsigned int Get_Proc_Mem_Max() const { return proc_mem_max_; }
    unsigned int Get_Page_Size_Max() const { return page_size_max_; }

    // Memory management.
    void Initialize_Mem();
    bool Allocate_Mem(PCB *a_process);
    void Deallocate_Mem(PCB *a_process);

    void Output_System_Memory_Info(ostream &out);
private:
    unsigned int mem_max_;
    unsigned int proc_mem_max_;
    unsigned int page_size_max_;

    set<unsigned int> free_frame_list_;
    map<unsigned int, std::pair<unsigned int, unsigned int>> frame_table_;
};

#endif
