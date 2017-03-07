#include "PCB.h"

string &PCB::Get_Parameters() {
    string &&parameters = "";
    for (auto param : parameters_) {
        parameters += param + "|";
    }

    return parameters;
}

ostream &operator<<(ostream &out, const PCB &a_PCB) {
    out << left
        << setw(5) << a_PCB.Get_PID();
        << setw(20) << "FILENAME"
        << setw(10) << "MEMSTART"
        << setw(5) << "R/W"
        << setw(20) << "FILE_LENGTH" << endl;

    return out;
}
