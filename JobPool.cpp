#include "JobPool.h"

PCB *JobPool::Find_Largest_Process(const unsigned int size_limit) {

}

void JobPool::Add_Process(PCB *a_process) {
    unsigned int page_table_size = a_process->Get_Page_Table_Size();
    pool_[page_table_size].push_back(a_process);
}

void JobPool::Remove_Pocess(PCB *a_process) {

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
