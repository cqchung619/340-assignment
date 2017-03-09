#include "CPU.h"

ostream &operator<<(ostream &out, const CPU &a_CPU) {
    out << "-----CPU Processes-----" << endl;
    out << left
        << setw(5) << "PID" << endl;
    a_CPU.process_queue_.Output_Processes(out, PCB::CPU);

    return out;
}
