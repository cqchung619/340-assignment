#include "PCB.h"

void PCB::Update_Process_Stats(double execution_time) {
    stats_.cpu_usage_time += execution_time;
    stats_.actual_burst_time += execution_time;
    stats_.burst_time_left -= execution_time;
}

void PCB::Update_Process_Stats(double execution_time, double history_parameter) {
    stats_.cpu_usage_time += execution_time;
    stats_.actual_burst_time += execution_time;
    stats_.estimated_burst_time = (history_parameter * stats_.estimated_burst_time) +
                                 ( (1 - history_parameter)  * stats_.actual_burst_time);
    stats_.burst_time_left = stats_.estimated_burst_time;
    stats_.total_burst_time += stats_.actual_burst_time;
    ++stats_.burst_count;
    stats_.actual_burst_time = 0;
}

double PCB::Get_Average_Burst_Time() {
    if (stats_.burst_count == 0) {
        return 0;
    }

    return stats_.total_burst_time / (double) stats_.burst_count;
}

void PCB::Output_PCB(ostream &out, OutputFormat format){
    switch (format) {
        case CPU:
            out << right
                << setw(5) << PID_
                << setw(20) << (double) Get_CPU_Usage_Time()
                << setw(20) << (double) Get_Average_Burst_Time();
            break;
        case DEVICE:
            out << right
                << setw(3) << PID_
                << left
                << setw(9) << ( "  " + parameters_[0] )
                << right
                << setw(10) << parameters_[1]
                << setw(5) << parameters_[2]
                << left
                << setw(13) << ( "  " + parameters_[3] )
                << right
                << setw(14) << (double) Get_CPU_Usage_Time()
                << setw(16) << (double) Get_Average_Burst_Time();
            break;
        case DISK:
            out << right
                << setw(3) << PID_
                << left
                << setw(9) << ( "  " + parameters_[0] )
                << right
                << setw(10) << parameters_[1]
                << setw(5) << parameters_[2]
                << left
                << setw(13) << ( "  " + parameters_[3] )
                << setw(10) << ( "  " + parameters_[4] )
                << right
                << setw(14) << (double) Get_CPU_Usage_Time()
                << setw(16) << (double) Get_Average_Burst_Time();
            break;
    }

    out << endl;
}
