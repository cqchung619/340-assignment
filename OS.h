/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#ifndef OS_H
#define OS_H

#include "CPU.h"
#include "Device.h"
#include "PCB.h"
#include "PCBQueue.h"

#include <iostream>
#include <map>
using namespace std;

class OS {
public:
    OS(): running_{true}, PID_counter_{0}, cpu_{new CPU}, ready_queue_{new PCBQueue} {}
    ~OS() {
        delete cpu_;
        delete ready_queue_;
        for (auto table : device_table_) {
            for (auto item : table.second) {
                delete item.second;
            }
        }
    }

    // @device_count: Holds the number of each devie to be created.
    //                Order of the numbers is printer, disk, CD/RW.
    void Initialize_Devices(const vector<unsigned int> &device_count);

    void Run();

private:
    bool running_;
    unsigned int PID_counter_;
    CPU *cpu_;
    PCBQueue* ready_queue_;
    map<string, map<string, Device*>> device_table_;

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
