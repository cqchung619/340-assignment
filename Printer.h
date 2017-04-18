#ifndef PRINTER_H
#define PRINTER_H

#include "Device.h"

class Printer: public Device {
public:
    Printer(const string &a_name): name_{a_name}, process_queue_{new PCBQueue} {}
private:
};

#endif
