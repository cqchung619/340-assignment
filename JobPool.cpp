#include "JobPool.h"

PCB *JobPool::Find_Largest_Process(const unsigned int size_limit) {

}

void JobPool::Add_Process(PCB *a_process) {
    unsigned int page_table_size = a_process->Get_Page_Table_Size();
    if ( pool_.count(page_table_size) == 0 ) {
        pool_[page_table_size] = new PCBQueue;
        pool_[page_table_size]->enqueue(a_process);
    } else {
        pool_[page_table_size]->enqueue(a_process);
    }
}

void JobPool::Remove_Pocess(PCB *a_process) {

}

void JobPool::Output_Job_Pool() {

}
