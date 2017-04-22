/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #2: Pre-Emptive SJF, Disk Scheduling and Accounting
*/

#ifndef CD_H
#define CD_H

#include "Device.h"

class CD: public Device {
public:
    CD(const string &a_name): Device::Device{a_name} {}

    virtual ~CD() {}
private:
};

#endif
