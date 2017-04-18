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
