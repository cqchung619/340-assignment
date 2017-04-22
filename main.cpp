/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #2: Pre-Emptive SJF, Disk Scheduling and Accounting
*/

#include "OS.h"
#include "SystemGenerator.h"
using namespace std;

int main() {
    SystemGenerator sys_gen;
    OS system340 = sys_gen.Generate_OS();
    system340.Run();

    return 0;
}
