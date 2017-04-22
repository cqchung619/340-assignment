/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #2: Pre-Emptive SJF, Disk Scheduling and Accounting
*/

#ifndef DISK_H
#define DISK_H

#include "Device.h"

class Disk: public Device {
public:
    Disk(const string &a_name, const unsigned int n): Device::Device{a_name}, number_of_cylinders_{n} {}

    virtual ~Disk() {}

    // Operator<< overload.
    friend ostream &operator<<(ostream &out, const Disk &a_disk);

private:
    unsigned int number_of_cylinders_;
};

#endif
