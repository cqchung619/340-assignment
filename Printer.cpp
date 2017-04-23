#include "Printer.h"

ostream &operator<<(ostream &out, const Printer &a_printer) {
    out << "-----" << a_printer.name_ << "-----" << endl;
    a_printer.process_queue_->Output_Processes(out, PCB::DEVICE);

    return out;
}
