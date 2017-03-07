#include "Device.h"

ostream &operator<<(ostream &out, const Device &a_device) {
    out << left
        << setw(5) << "PID"
        << setw(20) << "FILENAME"
        << setw(10) << "MEMSTART"
        << setw(5) << "R/W"
        << setw(20) << "FILE_LENGTH" << endl;

    out << "-----" << a_device.name_ << "-----" << endl;
    out << a_device.process_queue_;

    return out;
}
