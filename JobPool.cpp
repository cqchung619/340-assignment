#include "JobPool.h"

PCB *JobPool::Find_Largest_Process(const unsigned int size_limit) {
    unsigned int largest_page_table_size = 0;
    for (auto item : pool_) {
        if (item.first <= size_limit) {
            largest_page_table_size = item.first;
        } else {
            break;
        }
    }

    if (largest_page_table_size == 0) {
        return nullptr;
    } else {
        return pool_[largest_page_table_size].front();
    }

}

void JobPool::Add_Process(PCB *a_process) {
    unsigned int page_table_size = a_process->Get_Page_Table_Size();
    pool_[page_table_size].push_back(a_process);
}

void JobPool::Remove_Pocess(PCB *a_process) {
    unsigned int page_table_size = a_process->Get_Page_Table_Size();
    if (pool_[page_table_size].size() == 1) {
        pool_.erase(page_table_size);
    } else {
        pool_[page_table_size].pop_front();
    }
}

void JobPool::Output_Job_Pool(ostream& out) {
    for (auto item : pool_) {
        for (auto process : item.second) {
            out << right
                << setw(5) << process->Get_PID()
                << setw(5) << process->Get_SIZE()
                << endl;
        }
    }
}
