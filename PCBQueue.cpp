#include "PCBQueue.h"

PCB *PCBQueue::dequeue() {
    if (empty()) {
        return nullptr;
    }
    PCB *a_PCB = process_list_.front();
    process_list_.pop_front();

    return a_PCB;
}

ostream &operator<<(ostream &out, const PCBQueue &a_PCB_Queue) {
    for (auto it = a_PCB_Queue.process_list_.begin(); it != a_PCB_Queue.process_list_.end(); ++it) {
        out << *(*it) << endl;
    }

    return out;
}
