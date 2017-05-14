/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #3: Paging, Memory Management
*/

#ifndef OS_H
#define OS_H

#include "CD.h"
#include "CPU.h"
#include "Device.h"
#include "Disk.h"
#include "JobPool.h"
#include "MMU.h"
#include "PCB.h"
#include "PCBQueue.h"
#include "Printer.h"
#include "ReadyQueue.h"

#include <iostream>
#include <map>
#include <sstream>
using namespace std;

class OS {
public:
    OS(): running_{true}, PID_counter_{0},
          total_cpu_usage_time_{0}, number_of_completed_processes_{0},
          mmu_{new MMU}, job_pool_{new JobPool}, cpu_{new CPU}, ready_queue_{new ReadyQueue} {}
    ~OS() {
        delete mmu_;
        delete cpu_;
        delete ready_queue_;
        for (auto printer : printer_table_) {
            delete printer.second;
        }
        for (auto disk : disk_table_) {
            delete disk.second;
        }
        for (auto cd : cd_table_) {
            delete cd.second;
        }
    }

    void Set_History_Alpha(const double alpha) { history_alpha_ = alpha; }
    void Set_Initial_Burst_Tau(const double tau) { initial_burst_tau_ = tau; }

    void Initialize_Memory(const unsigned int mem, const unsigned int proc_size, const unsigned int page_size);

    void Initialize_Printers(const unsigned int number_of_printers);
    void Initialize_Disks(const vector<unsigned int> &number_of_disks);
    void Initialize_CDs(const unsigned int number_of_CDs);

    void Run();

private:
    bool running_;

    // Process Information.
    unsigned int PID_counter_;
    double history_alpha_; // Between 0 and 1.
    double initial_burst_tau_; // milliseconds.

    // OS Statistics.
    double total_cpu_usage_time_;
    double number_of_completed_processes_;

    // Memory Management Unit.
    MMU *mmu_;

    // Processes not in memory.
    JobPool *job_pool_;

    // CPU
    CPU *cpu_;
    ReadyQueue* ready_queue_;

    // Devices
    map<string, Printer*> printer_table_;
    map<string, Disk*> disk_table_;
    map<string, CD*> cd_table_;

    /////////////////// Input Functions ///////////////////

    // Input validator for interrupts and system calls.
    // Verifies that device exists.
    // Valid only if length 1 or 2.
    // Length 1: A, S, t
    // Length 2: (p/d/c)#, (P/D/C)#
    bool Is_Valid_Signal_Input(const string &an_input);

    // Validates a non-empty, numeric input.
    bool Is_Valid_Numeric_Input(const string& user_input);

    // Processes the input to determine if the Interrupr Handler or the System Call Handler should be used.
    // Interrupt: A, S (P/D/C)#
    // System Call: t, (p/d/c)#
    void Process_Input(const string &an_input);

    ////////////////// Interrupt Handler //////////////////

    // Interrupr Handler function.
    // Assumes valid input and device exists
    void Handle_Interrupt(const string &an_input);

    void Create_Process();
    void Snapshot();
    void Signal_Device_Completion(Device *a_device);

    ////////////////// System Calls //////////////////

    // System Call Handler function.
    // Assumes valid input and device exists.
    void Handle_Sys_Call(const string &an_input);

    // Remove PCB from CPU and front of Ready Queue.
    // Take PCB from the front of ready queue and put into CPU.
    void Terminate_Running_Process(PCB *process);

    // Remove PCB from CPU
    // Get parameters
    // Put PCB into device queue
    // Take PCB from the front of ready queue and put into CPU.
    void Request_Printer(PCB *process, Printer *a_printer);
    void Request_Disk(PCB *process, Disk *a_disk);
    void Request_Optical_Drive(PCB *process, CD *an_optical_drive);

    void Acquire_Printer_Parameters(PCB *a_process);
    void Acquire_Disk_Parameters(PCB *a_process, Disk *target_disk);
    void Acquire_Optical_Drive_Parameters(PCB *a_process);

    double Query_Timer();
};

#endif
