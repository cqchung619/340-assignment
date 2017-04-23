// Queue implemented as a reverse vector. Highest priority (lower cylinder number) in the back.

#ifndef DISK_QUEUE_H
#define DISK_QUEUE_H

#include <iostream>
#include <vector>
using namespace std;

class DiskQueue {
public:
    DiskQueue(): queue_head_{nullptr}, queue_tail_{nullptr}, seek_head_{nullptr} {}
    ~DiskQueue() {}

    // Returns true if queue is empty, otherwise returns false.
    bool empty() const { return current_size_ == 0; }

    // Returns number of PCBs in queue.
    size_t size() const { return current_size_; }

    // Adds process to the back of the queue.
    void enqueue(PCB *a_process);

    // Removes the process in front of the queue and returns a copy.
    // Assumes queue is non-empty.
    PCB *dequeue();

    // Returns a reference to the process in the front of the queue.
    // Assumes queue is non-empty.
    PCB *front();

    // Returns a reference to the process in the back of the queue.
    // Assumes queue is non-empty.
    PCB *back();

    // Outputs the process_list_ to out in the specified format.
    void Output_Processes(ostream &out, PCB::OutputFormat format) const;

private:
    struct Node {
        PCB *process;
        unsigned int cylinder_accessed;
        Node *next;

        Node(PCB *a_process): process{a_process}, cylinder_accessed{process->Get_Parameter(4)}, next{nullptr} {}
    };

    Node *queue_head_;
    Node *queue_tail_;
    Node *seek_head_;
    size_t current_size_;
};

#endif
