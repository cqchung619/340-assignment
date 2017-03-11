#include "Device.h"

ostream &operator<<(ostream &out, const Device &a_device) {
    out << "-----" << a_device.name_ << "-----" << endl;
    a_device.process_queue_.Output_Processes(out, PCB::DEVICE);

    return out;
}
