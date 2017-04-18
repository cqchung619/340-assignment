#ifndef CD_H
#define CD_H

#include "Device.h"

class CD: public Device {
public:
    CD(const string &a_name): name_{a_name}, process_queue_{new PCBQueue} {}
private:
};

#endif
