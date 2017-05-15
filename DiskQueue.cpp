#include "DiskQueue.h"

void DiskQueue::enqueue(PCB *a_process) {
    Node *new_node = new Node{a_process};
    unsigned int cylinder = new_node->cylinder_accessed;

    Node *temp = queue_head_;
    if (current_size_ == 0) { // Empty queue. Insert and set seek head to new node(immediately process).
        queue_head_ = new_node;
        queue_tail_ = new_node;
        queue_tail_->next = queue_head_;
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
        if ( (temp->next == seek_head_) && (cylinder == seek_head_->cylinder_accessed) ) {
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
    PCB *removed_process = seek_head_->process;
    Node *temp = queue_head_;

    if (current_size_ == 1) { // Single item.
        queue_head_ = nullptr;
        queue_tail_ = nullptr;
        seek_head_ = nullptr;
    } else if (seek_head_ == queue_head_) { // seek head is at the front.
        seek_head_ = seek_head_->next;
        queue_head_ = queue_head_->next;
        queue_tail_->next = queue_head_;
    } else {
        // Move to node before seek head.
        while ( (temp->next != seek_head_) ) {
            temp = temp->next;
        }

        if (seek_head_ == queue_tail_) { // seek head is at the end.
            seek_head_ = seek_head_->next;
            queue_tail_ = temp;
            temp = temp->next;
            queue_tail_->next = queue_head_;
        } else { // seek head is within the queue.
            temp->next = seek_head_->next;
            temp = seek_head_;
            seek_head_ = seek_head_->next;
        }
    }

    // clean up.
    temp->process = nullptr;
    temp->next = nullptr;
    delete temp;
    --current_size_;

    return removed_process;
}

PCB *DiskQueue::remove(const unsigned int pid) {
    if (empty()) {
        return nullptr;
    }

    Node *temp = queue_tail_;
    while (temp->next->process->Get_PID() != pid) { // Advance temp to node before desired node if it exists.
        temp = temp->next;
        if (temp->next == queue_head_) { // Not found.
            return nullptr;
        }
    }

    PCB *removed_process = temp->process;
    // Removal sequence.
    if (current_size_ == 1) { // Single item.
        queue_head_ = nullptr;
        queue_tail_ = nullptr;
        seek_head_ = nullptr;
    } else if (temp->next == queue_head_) { // removed node is at the front.
        temp = temp->next;
        queue_head_ = queue_head_->next;
        queue_tail_->next = queue_head_;
        if (temp == seek_head_) {
            seek_head_ = seek_head_->next;
        }
    } else if (temp->next == queue_tail_) { // removed node is at the end.
        queue_tail_ = temp;
        temp = temp->next;
        queue_tail_->next = queue_head_;
        if (temp == seek_head_) {
            seek_head_ = seek_head_->next;
        }
    } else { // removed node is in the middle.
        Node *temp2 = temp; // Require another Node* to keep track of current temp;
        temp = temp->next; // |temp2|->|temp|->|node|
        temp2->next  = temp->next; // |temp2|->|node|, |temp|
        if (temp == seek_head_) {
            seek_head_ = seek_head_->next;
        }

        temp2 = nullptr;
    }

    // clean up.
    temp->process = nullptr;
    temp->next = nullptr;
    delete temp;
    --current_size_;

    return removed_process;
}

PCB *DiskQueue::front() {
    if (empty()) {
        return nullptr;
    }

    return queue_head_->process;
}

PCB *DiskQueue::back() {
    if (empty()) {
        return nullptr;
    }

    return queue_tail_->process;
}

void DiskQueue::Output_Processes(ostream &out, PCB::OutputFormat format) const {
    if (current_size_ == 0) {
        return;
    }

    Node *temp = seek_head_;
    do {
        temp->process->Output_PCB(out, format);
        out << "|___Page Table: "
            << temp->process->Get_Frame_List_String()
            << endl;
        temp = temp->next;
    } while (temp != seek_head_);
}
