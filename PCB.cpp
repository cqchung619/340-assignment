#include "PCB.h"

void PCB::Output_PCB(ostream &out, OutputFormat format) const{
    switch (format) {
        case CPU:
            out << right
                << setw(5) << PID_;
            break;
        case DEVICE:
            out << right
                << setw(5) << PID_
                << left
                << setw(20) << (" " + parameters_[0])
                << right
                << setw(10) << parameters_[1]
                << setw(5) << parameters_[2]
                << left
                << setw(20) << (" " + parameters_[3]);
            break;
    }

    out << endl;
}
