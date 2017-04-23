#include "ReadyQueue.h"

void ReadyQueue::enqueue(PCB *a_process) {
    // Empty queue, push back.
    if (process_list_.empty()) {
        process_list_.push_back(a_process);
        return;
    }

    // Find position in queue based on burst time left and insert.
    for (auto it = process_list_.begin(); it != process_list_.end(); ++it) {
        if (a_process->Get_Burst_Time_Left() < (*it)->Get_Burst_Time_Left()) {
            process_list_.insert(it, a_process);
            return;
        }
    }

    // Should go at the end of the list, psuh back.
    process_list_.push_back(a_process);
    return;
}