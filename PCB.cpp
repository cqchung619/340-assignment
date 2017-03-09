#include "PCB.h"

void PCB::Output_PCB(ostream &out, OutputFormat format) const{
    switch (format) {
        case CPU:
            out << left
                << setw(5) << PID_;
            break;
        case DEVICE:
            out << left
                << setw(5) << PID_
                << setw(20) << parameters_[0]
                << setw(10) << parameters_[1]
                << setw(5) << parameters_[2]
                << setw(20) << parameters_[3];
            break;
    }

    out << endl;
}
