#include "OS.h"

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
            cout << "Invalid\n" << endl;;
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
        case 2: { // (P/D/C)#, (p/d/c)#
            if (isalpha(an_input[0]) && isdigit(an_input[1])) { // (letter)(number)
                string temp = an_input;

                // Check if the device exists.
                if (isupper(an_input[0])) { // If uppercase convert to lowercase
                    temp[0] = tolower(an_input[0]);
                }

                is_valid = printer_table_.count(temp) != 0 ||
                           disk_table_.count(temp) != 0 ||
                           cd_table_.count(temp) != 0;
            }

            break;
        }
        default:
            if (an_input == "EXIT" || an_input == "exit") {
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

    for (size_t i = 0; i < user_input.length(); i++) {
        if (!isdigit(user_input[i])) {
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
            cout << "Process created.\n";
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
    }

    cout << endl;
    if (!ready_queue_->empty()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Create_Process() {
    PCB *new_process = new PCB(PID_counter_++, initial_burst_tau_);
    ready_queue_->enqueue(new_process);
}

void OS::Snapshot() {
    string an_input = "";
    bool valid_input = false;
    do {
        cout << "Select an option (r/p/d/c):\n> ";
        getline(cin, an_input);

        valid_input = an_input == "r" || an_input == "p" ||
                      an_input == "d" || an_input == "c";
    } while (!valid_input);

    cout << "SYSTEMS AVERAGE CPU TIME: "
         << ( (number_of_completed_processes_ == 0) ? 0 : (total_cpu_usage_time_ / number_of_completed_processes_) )
         << endl;

    if (an_input == "r") {
        cout << "---Ready Queue---" << endl;
        cout << right
             << setw(5) << "PID"
             << setw(20) << "TOTAL_CPU_TIME"
             << setw(20) << "AVG_BURST_TIME"
             << endl;
        ready_queue_->Output_Processes(cout, PCB::CPU);
    } else {
        cout << right
             << setw(3) << "PID"
             << left
             << setw(9) << " FILENAME"
             << right
             << setw(10) << "MEMSTART"
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
    total_cpu_usage_time_ += process->Get_CPU_Usage_Time();
    ++number_of_completed_processes_;

    cout << "SYSTEM AVERAGE CPU TIME: "
         << ( (number_of_completed_processes_ == 0) ? 0 : (total_cpu_usage_time_ / number_of_completed_processes_) )
         << endl;

    cout << "PID: " << process->Get_PID()
         << "\tTotal CPU time: " << process->Get_CPU_Usage_Time()
         << "\tAverage burst time: " << process->Get_Average_Burst_Time()
         << endl;

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

void OS::Acquire_Printer_Parameters(PCB *a_process) {
    string param = "";

    // Filename
    do {
        cout << "What is the filename?\n> ";
        getline(cin, param);
    } while (param == "");
    a_process->Add_Param(param);

    // Memstart
    do {
        cout << "Where is the memstart location (numerical)?\n> ";
        getline(cin, param);
    } while (param == "" || !Is_Valid_Numeric_Input(param));
    a_process->Add_Param(param);

    // R/W
    param = "W";
    a_process->Add_Param(param);

    // File Length
    do {
        cout << "What is the file length (numerical)?\n> ";
        getline(cin, param);
    } while (param == "" || !Is_Valid_Numeric_Input(param));
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
    do {
        cout << "Where is the memstart location (numerical)?\n> ";
        getline(cin, param);
    } while (param == "" || !Is_Valid_Numeric_Input(param));
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
            cout << "Invalid input. Which cylinder will be accessed?\n> ";
            getline(cin, param);
        } else if ( (unsigned int) stoi(param) > target_disk->Get_Cylinder_Count() - 1 ) {
            validated = false;
            cout << "Invalid cylinder. Which cylinder will be accessed (0 - "
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
    do {
        cout << "Where is the memstart location (numerical)?\n> ";
        getline(cin, param);
    } while (param == "" || !Is_Valid_Numeric_Input(param));
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

double OS::Query_Timer() {
    string input = "";

    double elapsed_time = 0;
    cout << "How much time has pass (milliseconds)?\n> ";
    while (true) {
        getline(cin, input);

        istringstream double_stream{input};
        if ( (double_stream >> elapsed_time) && (elapsed_time >= 0) ){
            break;
        }
        elapsed_time = 0;

        cout << "Invalid input. How much time has passed?\n> ";
    }

    return elapsed_time;
}
