/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #3: Paging, Memory Management
*/

#ifndef PCB_H
#define PCB_H

#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class PCB {
public:
    enum OutputFormat { CPU, DEVICE, DISK };

    // @a_PID: OS assigned integer value.
    // All newly constructed PCBs are in the NEW state.
    PCB(const unsigned int a_PID, const unsigned int pages, const unsigned int size, double initial_burst)
    : PID_{a_PID}, SIZE_{size}, number_of_pages_{pages} {
        stats_.cpu_usage_time = 0;
        stats_.actual_burst_time = 0;
        stats_.estimated_burst_time = initial_burst;
        stats_.burst_time_left = stats_.estimated_burst_time;
        stats_.total_burst_time = 0;
        stats_.burst_count = 0;
    }

    // @rhs: PCB to be copied.
    // Constructs a copy of rhs.
    PCB(const PCB &rhs)
    : PID_{rhs.PID_}, SIZE_{rhs.SIZE_}, number_of_pages_{rhs.number_of_pages_}, parameters_{rhs.parameters_} {}

    // PID/SIZE accessor. PID/SIZE never changes.
    const unsigned int &Get_PID() const { return PID_; }
    const unsigned int &Get_SIZE() const { return SIZE_; }

    //////////////////// Parameter accessor and modifier. ////////////////////

    const vector<string> &Get_Parameters() { return parameters_; }
    const string &Get_Parameter(const unsigned int index) { return parameters_[index]; }
    void Add_Param(const string &a_param) { parameters_.push_back(a_param); }
    void Clear_Params() { parameters_.clear(); }

    //////////////////// Accounting accessor and modifier. ////////////////////

    double Get_CPU_Usage_Time() { return stats_.cpu_usage_time; }
    double Get_Average_Burst_Time();
    double Get_Burst_Time_Left() { return stats_.burst_time_left; }

    // Interrupts
    void Update_Process_Stats(double execution_time);
    // System Calls
    void Update_Process_Stats(double execution_time, double history_parameter);

    //////////////////// Page Table functions. ////////////////////

    // Return number of pages.
    size_t Get_Page_Table_Size() { return number_of_pages_; }
    // Return frame number associated with page_number.
    unsigned int Get_Frame_At(const unsigned int page_number) { return page_table_[page_number]; }
    // Return a string of all frames being used in order by page number.
    string Get_Frame_List();
    // Update page table with frame number associated with each page number.
    void Update_Page_Table(const vector<unsigned int> &allocated_frame_list);
    // Clear page table. Process's memory is being deallocated.
    void Clear_Page_Table() { page_table_.clear(); }

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
    const unsigned int SIZE_;
    unsigned int number_of_pages_;

    map<unsigned int, unsigned int> page_table_;

    // Contents should be:
    // Filename , Memstart , R/W , File Length, Cylinder(Disk Only)
    // in this exact order.
    vector<string> parameters_;
};

#endif
