#include "PCBQueue.h"

PCB PCBQueue::dequeue() {
    // if (empty()) {
    //     return NULL;
    // }
    PCB a_PCB{process_list_.front()};
    process_list_.pop_front();

    return a_PCB;
}

PCB &PCBQueue::front() {
    // if (empty()) {
    //     return NULL;
    // }
    PCB &front_PCB = process_list_.front();
    return front_PCB;
}

PCB &PCBQueue::back() {
    // if (empty()) {
    //     return NULL;
    // }
    PCB &back_PCB = process_list_.back();
    return back_PCB;
}

ostream &operator<<(ostream &out, const PCBQueue &a_PCB_Queue) {
    for (auto it = a_PCB_Queue.process_list_.begin(); it != a_PCB_Queue.process_list_.end(); ++it) {
        out << *it << endl;
    }

    return out;
}
