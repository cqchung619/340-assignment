#include "Disk.h"

ostream &operator<<(ostream &out, const Disk &a_disk) {
    out << "-----"
        << a_disk.name_
        << " "
        << a_disk.number_of_cylinders_
        << ((a_disk.number_of_cylinders_ == 1) ? " cylinder" : " cylinders")
        << "-----"
        << endl;
    a_disk.process_queue_->Output_Processes(out, PCB::DEVICE);

    return out;
}
