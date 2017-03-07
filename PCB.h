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

    PCB(const unsigned int a_PID, const unsigned int a_mem_location): state_{PCB::NEW}, PID_(a_PID), memstart_{a_mem_location} {}

    State &Get_State() { return state_; }
    void Change_State(const State new_state) { state_ = new_state; }

    const unsigned int &Get_PID() const { return PID_; }

    const unsigned int &Get_Memstart() const { return memstart_; }
    void Change_Memstart(const unsigned int new_mem_location) { memstart_ = new_mem_location; }

    string &Get_Parameters();
    void Add_Param(const string &a_param) { parameters_.push_back(a_param); }
    void Clear_Params() { parameters_.clear(); }

    friend ostream &operator<<(ostream &out, const PCB &a_PCB);


private:
    State state_;
    const unsigned int PID_;
    unsigned int memstart_;
    vector<string> parameters_;
};

#endif
