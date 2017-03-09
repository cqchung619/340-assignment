#include "PCB.h"

ostream &operator<<(ostream &out, const PCB &a_PCB) {
    out << left
        << setw(5) << a_PCB.Get_PID()
        << setw(20) << a_PCB.parameters_[0]
        << setw(10) << a_PCB.parameters_[1]
        << setw(5) << a_PCB.parameters_[2]
        << setw(20) << a_PCB.parameters_[3];

    return out;
}
