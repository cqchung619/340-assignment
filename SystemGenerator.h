#ifndef SYS_GEN_H
#define SYS_GEN_H

#include "OS.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

class SystemGenerator {
public:
    OS Generate_OS();

private:
    bool Is_Valid_Numeric_Input(const string& user_input);

    void Generate_Printers(OS &an_OS);
    void Generate_Disks(OS &an_OS);
    void Generate_CDs(OS &an_OS);

    void Set_Initial_CPU_Scheduling_Values(OS &an_OS);
};

#endif
