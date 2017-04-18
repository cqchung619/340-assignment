#ifndef PRINTER_H
#define PRINTER_H

#include "Device.h"

class Printer: public Device {
public:
    Printer(const string &a_name): Device::Device{a_name} {}

    virtual ~Printer() {}
private:
};

#endif
