/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef OS_H
#define OS_H

#include "CD.h"
#include "CPU.h"
#include "Device.h"
#include "Disk.h"
#include "PCB.h"
#include "PCBQueue.h"
#include "Printer.h"

#include <iostream>
#include <map>
using namespace std;

class OS {
public:
    OS(): running_{true}, PID_counter_{0}, cpu_{new CPU}, ready_queue_{new PCBQueue} {}
    ~OS() {
        delete cpu_;
        delete ready_queue_;
        for (auto printer : printer_table_) {
            delete printer.second;
        }
        for (auto disk : disk_table_) {
            delete disk.second;
        }
        for (auto cd : cd_table_) {
            delete cd   .second;
        }
    }

    void Set_History_Alpha(const double alpha) { history_alpha_ = alpha; }
    void Set_Burst_Tau(const double tau) { burst_tau_ = tau; }

    void Initialize_Printers(const unsigned int number_of_printers);
    void Initialize_Disks(const vector<unsigned int> &number_of_disks);
    void Initialize_CDs(const unsigned int number_of_CDs);

    void Run();

private:
    bool running_;
    unsigned int PID_counter_;
    double history_alpha_; // Between 0 and 1.
    double burst_tau_; // milliseconds.
    CPU *cpu_;
    PCBQueue* ready_queue_;
    map<string, Printer*> printer_table_;
    map<string, Disk*> disk_table_;
    map<string, CD*> cd_table_;

    // Input validator for interrupts and system calls.
    // Verifies that device exists.
    // Valid only if length 1 or 2.
    // Length 1: A, S, t
    // Length 2: (p/d/c)#, (P/D/C)#
    bool Is_Valid_Signal_Input(const string &an_input);

    // Processes the input to determine if the Interrupr Handler or the System Call Handler should be used.
    // Interrupt: A, S (P/D/C)#
    // System Call: t, (p/d/c)#
    void Process_Input(const string &an_input);

    // Interrupr Handler function.
    // Assumes valid input and device exists
    void Handle_Interrupt(const string &an_input);

    // System Call Handler function.
    // Assumes valid input and device exists.
    void Handle_Sys_Call(const string &an_input);

    // Handles A input.
    void Create_Process();

    // Handles t input.
    void Terminate_Running_Process();

    // Handles S input and subsequent r, p, d, or c.
    void Snapshot();

    // Prompts for printer parameters:
    // filename, memstart, file length.
    // Printer is always write.
    void Acquire_Printer_Parameters(PCB *a_process);

    // Prompts for disk parameters:
    // filename, memstart, R/W, file length.
    // If R, file length is empty.
    void Acquire_Disk_Parameters(PCB *a_process);

    // Prompts for CD/RW parameters:
    // filename, memstart, R/W, file length.
    // If R, file length is empty.
    void Acquire_Optical_Drive_Parameters(PCB *a_process);

    // Validates a non-empty, numeric input.
    bool Is_Valid_Numeric_Input(const string& user_input);

    // Handles S -> p.
    void Request_Printer(Device *a_printer);

    // Handles S -> d.
    void Request_Disk(Device *a_disk);

    // Handles S -> c.
    void Request_Optical_Drive(Device *an_optical_drive);

    // Handles (P/D/C)#.
    void Signal_Device_Completion(Device *a_device);

    void test();
};

#endif
