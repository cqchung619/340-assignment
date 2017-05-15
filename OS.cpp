#include "OS.h"

void OS::Initialize_Memory(const unsigned int mem, const unsigned int proc_size, const unsigned int page_size) {
    mmu_->Set_Mem_Max(mem);
    mmu_->Set_Proc_Mem_Max(proc_size);
    mmu_->Set_Page_Size_Max(page_size);
    mmu_->Initialize_Mem();
}

void OS::Initialize_Printers(const unsigned int number_of_printers) {
    for (unsigned int i = 0; i < number_of_printers; ++i) {
        string name = "p" + to_string(i);
        Printer *printer = new Printer{name};
        printer_table_.insert(std::pair<string, Printer*>{name, printer});
    }
}

void OS::Initialize_Disks(const vector<unsigned int> &number_of_disks) {
    for (unsigned int i = 0; i < number_of_disks.size(); ++i) {
        string name = "d" + to_string(i);
        unsigned int cylinder_count = number_of_disks[i];
        Disk *disk = new Disk{name, cylinder_count};
        disk_table_.insert(std::pair<string, Disk*>{name, disk});
    }
}

void OS::Initialize_CDs(const unsigned int number_of_CDs) {
    for (unsigned int i = 0; i < number_of_CDs; ++i) {
        string name = "c" + to_string(i);
        CD *cd = new CD{name};
        cd_table_.insert(std::pair<string, CD*>{name, cd});
    }
}

void OS::Run() {
    while (running_) {
        cout << "> ";
        string input = "";
        getline(cin, input);

        if (Is_Valid_Signal_Input(input)) {
            Process_Input(input);
        } else {
            cout << "INVALID\n" << endl;;
        }
    }
}

/////////////////// Input Functions ///////////////////

bool OS::Is_Valid_Signal_Input(const string &an_input) {
    size_t input_length = an_input.length();
    bool is_valid = false;

    switch(input_length) {
        case 1: // A, S, t
            is_valid = an_input == "A" || an_input == "S" || an_input == "t";
            break;
        case 2: { // (P/D/C)#, (p/d/c)#, K#
            if (isalpha(an_input[0]) && isdigit(an_input[1])) { // (letter)(number)
                string temp = an_input;

                // Check if the device exists or signal is K.
                if (isupper(an_input[0])) { // If uppercase convert to lowercase
                    temp[0] = tolower(an_input[0]);
                }

                is_valid = printer_table_.count(temp) != 0 ||
                           disk_table_.count(temp) != 0 ||
                           cd_table_.count(temp) != 0 ||
                           an_input[0] == 'K';
            }

            break;
        }
        default:
            if (an_input[0] == 'K') { // K#, where # > 9.
                string temp = an_input.substr(1, an_input.length() -1);
                is_valid = Is_Valid_Numeric_Input(temp);
            } else if (an_input == "EXIT" || an_input == "exit") {
                is_valid = true;
            }

            break;
    }

    return is_valid;
}

bool OS::Is_Valid_Numeric_Input(const string& user_input) {
    if (user_input == "") {
        return false;
    }

    for (size_t i = 0; i < user_input.length(); ++i) {
        if (!isdigit(user_input[i])) {
            return false;
        }
    }

    return true;
}

bool OS::Is_Valid_Hex_Input(const string &user_input) {
    if (user_input == "") {
        return false;
    }

    for (size_t i = 0; i < user_input.length(); ++i) {
        if (!isxdigit(user_input[i])) {
            return false;
        }
    }

    return true;
}

void OS::Process_Input(const string &an_input) {
    switch (an_input.length()) {
        case 1:
            if (isupper(an_input[0])) {
                Handle_Interrupt(an_input);
            } else {
                Handle_Sys_Call(an_input);
            }
            break;
        case 2:
            if (isupper(an_input[0])) {
                Handle_Interrupt(an_input);
            } else {
                Handle_Sys_Call(an_input);
            }
            break;
        default:
            running_ = false;
            break;
    }
}

////////////////// Interrupt Handler //////////////////

void OS::Handle_Interrupt(const string &an_input) {
    // Pre-Emptive
    if (!cpu_->Is_Idle()) {
        double elapsed_time = Query_Timer();
        cpu_->Unbind_Process();
        PCB *interrupted_process = ready_queue_->dequeue();
        interrupted_process->Update_Process_Stats(elapsed_time);
        ready_queue_->enqueue(interrupted_process);
    }

    string temp = "";
    temp = tolower(an_input[0]);
    temp += an_input[1];


    switch (an_input[0]) {
        case 'A':
            Create_Process();
            break;
        case 'S':
            Snapshot();
            break;
        case 'P':
            if (printer_table_.find(temp)->second->Is_Idle()) {
                break;
            } else {
                Signal_Device_Completion(printer_table_.find(temp)->second);
                cout << "Current printer process complete.\n";
            }
            break;
        case 'D':
            if (disk_table_.find(temp)->second->Is_Idle()) {
                break;
            } else {
                Signal_Device_Completion(disk_table_.find(temp)->second);
                cout << "Current disk process complete.\n";
            }
            break;
        case 'C':
            if (cd_table_.find(temp)->second->Is_Idle()) {
                break;
            } else {
                Signal_Device_Completion(cd_table_.find(temp)->second);
                cout << "Current CD/RW process complete.\n";
            }
            break;
        case 'K':
            Kill_Process(an_input);
            break;
    }

    cout << endl;
    if (!ready_queue_->empty()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Create_Process() {
    string input = "";

    cout << "How big is the process?\n> ";
    getline(cin, input);
    while ( (!Is_Valid_Numeric_Input(input)) || !(stoi(input) > 0) ) {
        cout << "INVALID: Please enter a valid number:\n> ";
        getline(cin, input);
    }
    if ( (unsigned int) stoi(input) > mmu_->Get_Proc_Mem_Max() ) {
        cout << "REJECTED: Process is too big.\n";
        return;
    }
    unsigned int process_size = (unsigned int) stoi(input);
    unsigned int pages = 0;
    if ( (process_size % mmu_->Get_Page_Size_Max()) == 0 ) {
        pages = process_size / mmu_->Get_Page_Size_Max();
    } else {
        pages = (process_size / mmu_->Get_Page_Size_Max()) + 1;
    }

    PCB *new_process = new PCB(PID_counter_++, pages, process_size, initial_burst_tau_);
    bool mem_alloc_successful = mmu_->Allocate_Mem(new_process);
    if (!mem_alloc_successful) {
        job_pool_->Add_Process(new_process);
    } else {
        ready_queue_->enqueue(new_process);
    }

    cout << "Process created.\n";
}

void OS::Snapshot() {
    string an_input = "";
    bool valid_input = false;
    do {
        cout << "Select an option (r/p/d/c/m/j):\n> ";
        getline(cin, an_input);

        valid_input = an_input == "r" || an_input == "p" ||
                      an_input == "d" || an_input == "c" ||
                      an_input == "m" || an_input == "j";
    } while (!valid_input);

    cout << "SYSTEMS AVERAGE CPU TIME: "
         << ( (number_of_completed_processes_ == 0) ? 0 : (total_cpu_usage_time_ / number_of_completed_processes_) )
         << endl;

    if (an_input == "r") {
        cout << "-----Ready Queue-----" << endl;
        cout << right
             << setw(5) << "PID"
             << setw(20) << "TOTAL_CPU_TIME"
             << setw(20) << "AVG_BURST_TIME"
             << endl;
        ready_queue_->Output_Processes(cout, PCB::CPU);
    } else if (an_input == "m") {
        mmu_->Output_System_Memory_Info(cout);
    } else if (an_input == "j") {
        cout << "-----Job Pool-----" << endl;
        cout << right
             << setw(5) << "PID"
             << setw(5) << "SIZE"
             << endl;
        job_pool_->Output_Job_Pool(cout);
    } else {
        cout << right
             << setw(3) << "PID"
             << left
             << setw(14) << " FILENAME"
             << right
             << setw(5) << "ADDR"
             << setw(5) << "R/W"
             << left
             << setw(13) << "  FILE_LENGTH";

        if (an_input == "d") {
            cout << setw(10) << "  DISK_CYL";
        }

        cout << setw(14) << "  CPU_USE_TIME"
             << setw(16) << "  AVG_BURST_TIME"
             << endl;

        switch (an_input[0]) {
            case 'p':
                for (auto printer : printer_table_) {
                    cout << *(printer.second);
                }
                break;
            case 'd':
                for (auto disk : disk_table_) {
                    cout << *(disk.second);
                }
                break;
            case 'c':
                for (auto cd : cd_table_) {
                    cout << *(cd.second);
                }
                break;
        }
    }
}

void OS::Signal_Device_Completion(Device *a_device) {
    PCB *finished_process = a_device->Remove_Running_Process();
    finished_process->Clear_Params();
    ready_queue_->enqueue(finished_process);
}

void OS::Kill_Process(const string &input) {
    string temp = input.substr(1, input.length() - 1);
    unsigned int pid = (unsigned int) stoi(temp);

    PCB *killed_process = ready_queue_->remove(pid); // Not in ready queue.
    if (killed_process == nullptr) {
        for (auto item : printer_table_) { // Check printers.
            killed_process = item.second->Remove_Process(pid);
            if (killed_process != nullptr) { // Found.
                break;
            }
        }
    }
    if (killed_process == nullptr) {
        for (auto item : disk_table_) { // Check disks.
            killed_process = item.second->Remove_Process(pid);
            if (killed_process != nullptr) { // Found.
                break;
            }
        }
    }
    if (killed_process == nullptr) {
        for (auto item : cd_table_) { // Check cds.
            killed_process = item.second->Remove_Process(pid);
            if (killed_process != nullptr) { // Found.
                break;
            }
        }
    }
    if (killed_process == nullptr) {
        cout << "ERROR: Process " << pid << " does not exist in memory.\n";
        return;
    }

    Display_Terminated_Process_Stats(killed_process, false);

    mmu_->Deallocate_Mem(killed_process);
    Schedule_Eligible_Process();

    delete killed_process;
}

////////////////// System Calls //////////////////

void OS::Handle_Sys_Call(const string &an_input) {
    if (cpu_->Is_Idle()) {
        cout << "Error: No running process.\n" << endl;
        return;
    }

    // Burst finished, update all stats.
    double elapsed_time = Query_Timer();
    cpu_->Unbind_Process();
    PCB *calling_process = ready_queue_->dequeue();
    calling_process->Update_Process_Stats(elapsed_time, history_alpha_);

    switch (an_input[0]) {
        case 't':
            Terminate_Running_Process(calling_process);
            cout << "Process terminated.\n";
            break;
        case 'p':
            Request_Printer(calling_process, printer_table_.find(an_input)->second);
            cout << "Request handled successfully.\n";
            break;
        case 'd':
            Request_Disk(calling_process, disk_table_.find(an_input)->second);
            cout << "Request handled successfully.\n";
            break;
        case 'c':
            Request_Optical_Drive(calling_process, cd_table_.find(an_input)->second);
            cout << "Request handled successfully.\n";
            break;
    }

    cout << endl;
    if (!ready_queue_->empty()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Terminate_Running_Process(PCB *process) {
    Display_Terminated_Process_Stats(process, true);

    // Memory Management.
    mmu_->Deallocate_Mem(process);
    Schedule_Eligible_Process();

    delete process;
}

void OS::Request_Printer(PCB *process, Printer *a_printer) {
    // Get parameters and add to device queue.
    Acquire_Printer_Parameters(process);
    a_printer->Add_Process(process);
}

void OS::Request_Disk(PCB *process, Disk *a_disk) {
    // Get parameters and add to device queue.
    Acquire_Disk_Parameters(process, a_disk);
    a_disk->Add_Process(process);
}

void OS::Request_Optical_Drive(PCB *process, CD *an_optical_drive) {
    // Get parameters and add to device queue.
    Acquire_Optical_Drive_Parameters(process);
    an_optical_drive->Add_Process(process);
}

bool OS::Is_Valid_Memory_Access(PCB *a_process, const unsigned int address) {
    if (address > a_process->Get_SIZE()) { // address is outside process size range.
        return false;
    }

    unsigned int page_size = mmu_->Get_Page_Size_Max();
    unsigned int offset = address % page_size;
    if (offset > page_size) { // Offset goes beyond limit of a single frame.
        return false;
    }

    return true;
}

void OS::Convert_To_Pysical_Address(PCB *a_process, string &address) {
    unsigned int logical_address = stoi(address, nullptr, 16);
    unsigned int page_number = logical_address / mmu_->Get_Page_Size_Max();
    unsigned int offset = logical_address % mmu_->Get_Page_Size_Max();
    unsigned int physical_address = (a_process->Get_Frame_At(page_number) * mmu_->Get_Page_Size_Max()) + offset;

    ostringstream hex_address;
    hex_address << std::hex << std::uppercase << physical_address;
    address = hex_address.str();
}

void OS::Acquire_Printer_Parameters(PCB *a_process) {
    string param = "";

    // Filename
    do {
        cout << "What is the filename?\n> ";
        getline(cin, param);
    } while (param == "");
    a_process->Add_Param(param);

    // Memstart
    cout << "Where is the memstart address (hexadecimal)?\n> ";
    while (true) {
        getline(cin, param);
        if (!Is_Valid_Hex_Input(param)) {
            cout << "ERROR: Enter a valid address:\n> ";
        } else {
            unsigned int address = stoi(param, nullptr, 16);
            if ( !Is_Valid_Memory_Access(a_process, address) ) {
                cout << "ERROR: Invalid memory access. Enter a valid access:\n> ";
            } else {
                Convert_To_Pysical_Address(a_process, param);
                cout << "Physical address: " << param << endl;
                break;
            }
        }
    }
    a_process->Add_Param(param);

    // R/W
    param = "W";
    a_process->Add_Param(param);

    // File Length
    do {
        cout << "What is the file length (numerical)?\n> ";
        getline(cin, param);
    } while (!Is_Valid_Numeric_Input(param));
    a_process->Add_Param(param);
}

void OS::Acquire_Disk_Parameters(PCB *a_process, Disk *target_disk) {
    string param = "";

    // Filename
    do {
        cout << "What is the filename?\n> ";
        getline(cin, param);
    } while (param == "");
    a_process->Add_Param(param);

    // Memstart
    cout << "Where is the memstart address (hexadecimal)?\n> ";
    while (true) {
        getline(cin, param);
        if (!Is_Valid_Hex_Input(param)) {
            cout << "ERROR: Enter a valid address:\n> ";
        } else {
            unsigned int address = stoi(param, nullptr, 16);
            if ( !Is_Valid_Memory_Access(a_process, address) ) {
                cout << "ERROR: Invalid memory access. Enter a valid access:\n> ";
            } else {
                Convert_To_Pysical_Address(a_process, param);
                cout << "Physical address: " << param << endl;
                break;
            }
        }
    }
    a_process->Add_Param(param);

    // R/W
    do {
        cout << "Is this a read or write (r/w)?\n> ";
        getline(cin, param);
        param = toupper(param[0]);
    } while (param == "" || (param != "R" && param != "W"));
    a_process->Add_Param(param);

    // File Length
    if (param == "W") {
        do {
            cout << "What is the file length (numerical)?\n> ";
            getline(cin, param);
        } while (param == "" || !Is_Valid_Numeric_Input(param));
        a_process->Add_Param(param);
    } else {
        param = "";
        a_process->Add_Param(param);
    }

    // Cylinder
    cout << "Which cylinder will be accessed?\n> ";
    getline(cin, param);
    bool validated;
    do {
        validated = true;

        if ( (param == "") || (!Is_Valid_Numeric_Input(param)) ) { // Valid numeric input.
            validated = false;
            cout << "INVALID: Which cylinder will be accessed?\n> ";
            getline(cin, param);
        } else if ( (unsigned int) stoi(param) > target_disk->Get_Cylinder_Count() - 1 ) {
            validated = false;
            cout << "INVALID: Which cylinder will be accessed (0 - "
                 << target_disk->Get_Cylinder_Count() - 1
                 << ")?\n> ";
            getline(cin, param);
        }
    } while (!validated);
    a_process->Add_Param(param);
}

void OS::Acquire_Optical_Drive_Parameters(PCB *a_process) {
    string param = "";

    // Filename
    do {
        cout << "What is the filename?\n> ";
        getline(cin, param);
    } while (param == "");
    a_process->Add_Param(param);

    // Memstart
    cout << "Where is the memstart address (hexadecimal)?\n> ";
    while (true) {
        getline(cin, param);
        if (!Is_Valid_Hex_Input(param)) {
            cout << "ERROR: Enter a valid address:\n> ";
        } else {
            unsigned int address = stoi(param, nullptr, 16);
            if ( !Is_Valid_Memory_Access(a_process, address) ) {
                cout << "ERROR: Invalid memory access. Enter a valid access:\n> ";
            } else {
                Convert_To_Pysical_Address(a_process, param);
                cout << "Physical address: " << param << endl;
                break;
            }
        }
    }
    a_process->Add_Param(param);

    // R/W
    do {
        cout << "Is this a read or write (r/w)?\n> ";
        getline(cin, param);
        param = toupper(param[0]);
    } while (param == "" || (param != "R" && param != "W"));
    a_process->Add_Param(param);

    // File Length
    if (param == "W") {
        do {
            cout << "What is the file length (numerical)?\n> ";
            getline(cin, param);
        } while (param == "" || !Is_Valid_Numeric_Input(param));
        a_process->Add_Param(param);
    } else {
        param = "";
        a_process->Add_Param(param);
    }
}

void OS::Display_Terminated_Process_Stats(PCB *terminated_process, bool completed) {
    if (completed) {
        total_cpu_usage_time_ += terminated_process->Get_CPU_Usage_Time();
        ++number_of_completed_processes_;
    }

    cout << "SYSTEM AVERAGE CPU TIME: "
         << ( (number_of_completed_processes_ == 0) ? 0 : (total_cpu_usage_time_ / number_of_completed_processes_) )
         << endl;

    cout << "PID: " << terminated_process->Get_PID()
         << "\tTotal CPU time: " << terminated_process->Get_CPU_Usage_Time()
         << "\tAverage burst time: " << terminated_process->Get_Average_Burst_Time()
         << endl;
}

void OS::Schedule_Eligible_Process() {
    unsigned int number_of_free_frames = mmu_->Available_Mem_Size();
    PCB *eligible_process = job_pool_->Find_Largest_Process(number_of_free_frames);
    if (eligible_process != nullptr) {
        PCB *copy = new PCB{*eligible_process};
        mmu_->Allocate_Mem(copy);
        ready_queue_->enqueue(copy);
        job_pool_->Remove_Process(eligible_process);
    }
}

double OS::Query_Timer() {
    string input = "";

    double elapsed_time = 0;
    cout << "How much time has passed (milliseconds)?\n> ";
    while (true) {
        getline(cin, input);

        istringstream double_stream{input};
        if ( (double_stream >> elapsed_time) && (elapsed_time >= 0) ){
            break;
        }
        elapsed_time = 0;

        cout << "INVALID: How much time has passed?\n> ";
    }

    return elapsed_time;
}
