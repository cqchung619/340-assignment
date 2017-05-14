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

void PCB::Update_Page_Table(const vector<unsigned int> &allocated_frame_list) {
    for (size_t i = 0; i < page_table_.size(); ++i) {
        page_table_[i] = allocated_frame_list[i];
    }
}

string PCB::Get_Frame_List() {
    // page_table_.insert(std::pair<unsigned int, unsigned int>(0, 5));
    // page_table_.insert(std::pair<unsigned int, unsigned int>(1, 9));
    // page_table_.insert(std::pair<unsigned int, unsigned int>(2, 1));
    // page_table_.insert(std::pair<unsigned int, unsigned int>(3, 0));

    string frame_list = "";
    for (size_t i = 0; i < page_table_.size(); ++i) {
        if ( (i + 1) == page_table_.size() ) {
            frame_list += to_string(page_table_[i]);
        } else {
            frame_list += to_string(page_table_[i]) + ", ";
        }
    }

    return frame_list;
}

void PCB::Output_PCB(ostream &out, OutputFormat format){
    switch (format) {
        case CPU:
            out << left
                << "|"
                << right
                << setw(4) << PID_
                << setw(20) << (double) Get_CPU_Usage_Time()
                << setw(20) << (double) Get_Average_Burst_Time();
            break;
        case DEVICE:
            out << left
                << "|"
                << right
                << setw(2) << PID_
                << left
                << setw(14) << ( "  " + parameters_[0] )
                << right
                << setw(5) << parameters_[1]
                << setw(5) << parameters_[2]
                << left
                << setw(13) << ( "  " + parameters_[3] )
                << right
                << setw(14) << (double) Get_CPU_Usage_Time()
                << setw(16) << (double) Get_Average_Burst_Time();
            break;
        case DISK:
            out << left
                << "|"
                << right
                << setw(2) << PID_
                << left
                << setw(14) << ( "  " + parameters_[0] )
                << right
                << setw(5) << parameters_[1]
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
