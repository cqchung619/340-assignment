/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
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
    enum State { NEW, READY, RUNNING, WAITING };

    /*
     * @a_PID: OS assigned integer value.
     * All newly constructed PCBs are in the NEW state.
     */
    PCB(const unsigned int a_PID): state_{PCB::NEW}, PID_(a_PID) {}

    /*
     * State accessor and modifier.
     */
    State &Get_State() { return state_; }
    void Change_State(const State new_state) { state_ = new_state; }

    /*
     * PID accessor.
     * PID never changes.
     */
    const unsigned int &Get_PID() const { return PID_; }

    /*
     * Parameter accessor and modifier.
     */
    const vector<string> &Get_Parameters() { return parameters_; }
    void Add_Param(const string &a_param) { parameters_.push_back(a_param); }
    void Clear_Params() { parameters_.clear(); }

    /*
     * Operator<< overload.
     */
    friend ostream &operator<<(ostream &out, const PCB &a_PCB);

private:
    State state_;
    const unsigned int PID_;
    /*
     * Contents should be:
     * Filename , Memstart , R/W , File Length
     * in this exact order.
     */
    vector<string> parameters_;
};

#endif
