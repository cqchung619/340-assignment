#include "PCBQueue.h"

PCB *PCBQueue::dequeue() {
    if (empty()) {
        return nullptr;
    }
    PCB *a_PCB = process_list_.front();
    process_list_.pop_front();

    return a_PCB;
}

PCB *PCBQueue::remove(const unsigned int pid) {
    for (auto it = process_list_.begin(); it != process_list_.end(); ++it) {
        if ( (*it)->Get_PID() == pid ) {
            PCB *removed_process = *it;
            process_list_.erase(it);
            return removed_process;
        }
    }

    return nullptr;
}

PCB *PCBQueue::front() {
    if (empty()) {
        return nullptr;
    }

    return process_list_.front();
}

PCB *PCBQueue::back() {
    if (empty()) {
        return nullptr;
    }

    return process_list_.back();
}

void PCBQueue::Output_Processes(ostream &out, PCB::OutputFormat format) const {
    for (auto process : process_list_) {
        process->Output_PCB(out, format);
        out << "|___Page Table: "
            << process->Get_Frame_List_String()
            << endl;
    }
}
