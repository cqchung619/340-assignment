#include "DiskQueue.h"

void DiskQueue::enqueue(PCB *a_process) {
    Node *new_node = new Node{a_process};
    unsigned int cylinder = new_node->cylinder;

    Node *temp = queue_head_;
    if (current_size_ == 0) { // Empty queue. Insert and set seek head to new node(immediately process).
        queue_head_ = new_node;
        queue_tail_ = new_node;
        new_node->next = queue_head_;
        seek_head_ = new_node;
        ++current_size_;

        return;
    }

    if (cylinder < temp->cylinder_accessed) { // Insert at beginning.
        new_node->next = queue_head_;
        queue_head_ = new_node;
        queue_tail_->next = new_node;
        ++current_size_;

        return;
    }

    // Advance until right before the correct position where the new node should be inserted.
    while ( (temp->next->cylinder_accessed <= cylinder) && (temp != queue_tail_) ) {
        // Next node  is seek head (being processed) and cylinder accessed is the same.
        // We insert here behind the seek head.
        if ( (temp->next == seek_head_) && (cylinder == seek_head->cylinder_accessed) ) {
            break;
        }

        temp = temp->next;
    }

    if (temp == queue_tail_) { // Insert at the end.
        new_node->next = queue_head_;
        queue_tail_->next = new_node;
        queue_tail_ = new_node;
        ++current_size_;

        return;
    }

    // Insert within queue.
    new_node->next = temp->next;
    temp->next = new_node;
    ++current_size_;

    return;
}

PCB *DiskQueue::dequeue() {
    if (empty()) {
        return nullptr;
    }


    return a_PCB;
}

PCB *DiskQueue::front() {
    if (empty()) {
        return nullptr;
    }

    return process_list_.back();
}

PCB *DiskQueue::back() {
    if (empty()) {
        return nullptr;
    }

    return process_list_.front();
}

void DiskQueue::Output_Processes(ostream &out, PCB::OutputFormat format) const {
    // From seek_head to 0.
    for (size_t i = seek_head_; i >= 0; --i) {
        process_list_.at(i)->Output_PCB(out, format);
    }

    // From size - 1 to seek_head + 1.
    for (size_t i = process_list_.size() - 1; i >= seek_head_ + 1; --i) {
        process_list_.at(i)->Output_PCB(out, format);
    }
}
