#ifndef DISK_H
#define DISK_H

#include "Device.h"

class Disk: public Device {
public:
    Disk(const string &a_name, const unsigned int n) :
    name_{a_name}, number_of_cylinders_{n}, process_queue_{new PCBQueue} {}

    // Operator<< overload.
    friend ostream &operator<<(ostream &out, const Disk &a_disk);

private:
    unsigned int number_of_cylinders_;
};

#endif
