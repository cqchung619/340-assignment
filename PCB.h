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
    enum OutputFormat { CPU, DEVICE };

    // @a_PID: OS assigned integer value.
    // All newly constructed PCBs are in the NEW state.
    PCB(const unsigned int a_PID): PID_{a_PID}, cpu_usage_time_{0}, average_burst_time_{0} {}

    // @rhs: PCB to be copied.
    // Constructs a copy of rhs.
    PCB(const PCB &rhs): PID_{rhs.PID_}, parameters_{rhs.parameters_} {}

    // PID accessor. PID never changes.
    const unsigned int &Get_PID() const { return PID_; }

    // cpu_usage_time_ get/set
    unsigned int Get_CPU_Usage_Time() { return cpu_usage_time_; }
    void Set_CPU_Usage_Time(const unsigned int new_time) { cpu_usage_time_ = new_time; }

    // average_burst_time_ get/set
    unsigned int Get_Average_Burst_Time() { return average_burst_time_; }
    void Set_Average_Burst_Time(const unsigned int new_time) { average_burst_time_ = new_time; }

    // Parameter accessor and modifier.
    const vector<string> &Get_Parameters() { return parameters_; }
    void Add_Param(const string &a_param) { parameters_.push_back(a_param); }
    void Clear_Params() { parameters_.clear(); }

    // Outputs the PCB to out in the specified format.
    // If format is DEVICE, it assumes parameters_ has at least 4 elements.
    void Output_PCB(ostream &out, OutputFormat format) const;

private:
    const unsigned int PID_;
    unsigned int cpu_usage_time_;
    unsigned int average_burst_time_;

    // Contents should be:
    // Filename , Memstart , R/W , File Length
    // in this exact order.
    vector<string> parameters_;
};

#endif
