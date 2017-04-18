#include "Disk.h"

ostream &operator<<(ostream &out, const Device &a_disk) {
    out << "-----"
        << a_disk.name_
        << " "
        << a_disk.number_of_cylinders_
        << (a_disk.number_of_cylinders_ == 1) ? " cylinder" : " cylinders"
        << "-----" << endl;
    a_device.process_queue_->Output_Processes(out, PCB::DEVICE);

    return out;
}
