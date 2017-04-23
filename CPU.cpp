#include "CPU.h"

PCB* CPU::Unbind_Process() {
    PCB *a_process = running_process_;
    running_process_ = nullptr;

    return a_process;
}
