/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #2: Pre-Emptive SJF, Disk Scheduling and Accounting
*/

#ifndef PCB_H
#define PCB_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PCB {
public:
    enum OutputFormat { CPU, DEVICE, DISK };

    // @a_PID: OS assigned integer value.
    // All newly constructed PCBs are in the NEW state.
    PCB(const unsigned int a_PID, double initial_burst): PID_{a_PID} {
        stats_.cpu_usage_time = 0;
        stats_.actual_burst_time = 0;
        stats_.estimated_burst_time = initial_burst;
        stats_.burst_time_left = stats_.estimated_burst_time;
        stats_.total_burst_time = 0;
        stats_.burst_count = 0;
    }

    // @rhs: PCB to be copied.
    // Constructs a copy of rhs.
    PCB(const PCB &rhs): PID_{rhs.PID_}, parameters_{rhs.parameters_} {}

    // PID accessor. PID never changes.
    const unsigned int &Get_PID() const { return PID_; }

    // Parameter accessor and modifier.
    const vector<string> &Get_Parameters() { return parameters_; }
    const string &Get_Parameter(const unsigned int index) { return parameters_[index]; }
    void Add_Param(const string &a_param) { parameters_.push_back(a_param); }
    void Clear_Params() { parameters_.clear(); }

    double Get_CPU_Usage_Time() { return stats_.cpu_usage_time; }
    double Get_Average_Burst_Time();
    double Get_Burst_Time_Left() { return stats_.burst_time_left; }

    // Interrupts
    void Update_Process_Stats(double execution_time);
    // System Calls
    void Update_Process_Stats(double execution_time, double history_parameter);

    // Outputs the PCB to out in the specified format.
    // If format is DEVICE, it assumes parameters_ has at least 4 elements.
    void Output_PCB(ostream &out, OutputFormat format);

private:
    struct AccountingInformation {
        double cpu_usage_time;
        double actual_burst_time;
        double estimated_burst_time;
        double burst_time_left;
        double total_burst_time;
        unsigned int burst_count;

    } stats_;

    const unsigned int PID_;

    // Contents should be:
    // Filename , Memstart , R/W , File Length, Cylinder(Disk Only)
    // in this exact order.
    vector<string> parameters_;
};

#endif
