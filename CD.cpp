#include "CD.h"

ostream &operator<<(ostream &out, const CD &a_cd) {
    out << "-----" << a_cd.name_ << "-----" << endl;
    a_cd.process_queue_->Output_Processes(out, PCB::DEVICE);

    return out;
}
