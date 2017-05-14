#include "MMU.h"

void MMU::Initialize_Mem() {
    unsigned int number_of_frames = mem_max_ / page_size_max_;
    for (unsigned int i = 0; i < number_of_frames; ++i) {
        free_frame_list_.insert(i);
    }
}

bool MMU::Allocate_Mem(PCB *a_process) {
    if ( a_process->Get_Page_Table_Size() > Available_Mem_Size() ) {
        return false;
    }

    vector<unsigned int> allocated_frames;
    unsigned int pid = a_process->Get_PID();
    for (size_t i = 0; i < a_process->Get_Page_Table_Size(); ++i) {
        auto frame_number = free_frame_list_.begin();
        allocated_frames.push_back(*frame_number);

        std::pair<unsigned int, unsigned int> pid_and_page{pid, i};
        std::pair<unsigned int, std::pair<unsigned int, unsigned int>> frame_and_process{*frame_number, pid_and_page};
        frame_table_.insert(frame_and_process);
        free_frame_list_.erase(frame_number);
    }
    a_process->Update_Page_Table(allocated_frames);

    return true;
}

void MMU::Deallocate_Mem(PCB *a_process) {

}

void MMU::Output_System_Memory_Info(ostream &out) {
    out << "-----Frame Table-----\n"
        << right
        << setw(10) << "FRAME_NO."
        << setw(5) << "PID"
        << setw(10) << "PAGE_NO."
        << endl;
    for (auto item : frame_table_) {
        out << right
            << setw(10) << item.first
            << setw(5) << item.second.first
            << setw(10) << item.second.second
            << endl;
    }

    out << "Free Frame List:\n";
    unsigned int count = 0;
    auto it = free_frame_list_.begin();
    while ( it != free_frame_list_.end() ) {
        unsigned int frame_number = *it;
        if ( ++it == free_frame_list_.end() ) {
            out << setw(4) << frame_number;
            break;
        } else {
            out << setw(4) << frame_number << " ";
        }

        ++count;
        if (count % 10 == 0) {
            out << "\n";
        }
    }
    out << endl;
}
