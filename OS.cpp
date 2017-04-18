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

void OS::Handle_Interrupt(const string &an_input) {
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
}

void OS::Create_Process() {
    PCB *new_process = new PCB(PID_counter_++);
    ready_queue_->enqueue(new_process);
    if (cpu_->Is_Idle()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
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


    if (an_input == "r") {
        cout << "---Ready Queue---" << endl;
        cout << right
             << setw(5) << "PID"
             << setw(15) << " CPU_USAGE_TIME"
             << setw(15) << " AVG_BURST_TIME"
             << endl;
        ready_queue_->Output_Processes(cout, PCB::CPU);
    } else {
        cout << right
             << setw(5) << "PID"
             << left
             << setw(20) << " FILENAME"
             << right
             << setw(10) << "MEMSTART"
             << setw(5) << "R/W"
             << left
             << setw(20) << " FILE_LENGTH"
             << setw(15) << " CPU_USAGE_TIME"
             << setw(15) << " AVG_BURST_TIME"
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
    if (cpu_->Is_Idle()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Handle_Sys_Call(const string &an_input) {
    if (cpu_->Is_Idle()) {
        cout << "Error: No running process.\n" << endl;
        return;
    }

    switch (an_input[0]) {
        case 't':
            Terminate_Running_Process();
            cout << "Process terminated.\n";
            break;
        case 'p':
            Request_Printer(printer_table_.find(an_input)->second);
            cout << "Request handled successfully.\n";
            break;
        case 'd':
            Request_Disk(disk_table_.find(an_input)->second);
            cout << "Request handled successfully.\n";
            break;
        case 'c':
            Request_Optical_Drive(cd_table_.find(an_input)->second);
            cout << "Request handled successfully.\n";
            break;
    }

    cout << endl;
}

void OS::Terminate_Running_Process() {
    cpu_->Unbind_Process();
    PCB *terminated_process = ready_queue_->dequeue();
    delete terminated_process;
    if (!ready_queue_->empty()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Request_Printer(Device *a_printer) {
    // Unbind process from CPU and remove from ready_queue_.
    cpu_->Unbind_Process();
    PCB *calling_process = ready_queue_->dequeue();

    // Get parameters and add to device queue.
    Acquire_Printer_Parameters(calling_process);
    a_printer->Add_Process(calling_process);

    // Bind next process to CPU if available.
    if (!ready_queue_->empty()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Request_Disk(Device *a_disk) {
    // Unbind process from CPU and remove from ready_queue_.
    cpu_->Unbind_Process();
    PCB *calling_process = ready_queue_->dequeue();

    // Get parameters and add to device queue.
    Acquire_Disk_Parameters(calling_process);
    a_disk->Add_Process(calling_process);

    // Bind next process to CPU if available.
    if (!ready_queue_->empty()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Request_Optical_Drive(Device *an_optical_drive) {
    // Unbind process from CPU and remove from ready_queue_.
    cpu_->Unbind_Process();
    PCB *calling_process = ready_queue_->dequeue();

    // Get parameters and add to device queue.
    Acquire_Optical_Drive_Parameters(calling_process);
    an_optical_drive->Add_Process(calling_process);

    // Bind next process to CPU if available.
    if (!ready_queue_->empty()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
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

void OS::Acquire_Disk_Parameters(PCB *a_process) {
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

void OS::test() {
    Device d1{"printer 1"};
    // CPU d1;
    PCB *p0 = new PCB{0};
    p0->Add_Param("input.txt");
    p0->Add_Param("132");
    p0->Add_Param("W");
    p0->Add_Param("31");

    cout << d1 << endl;
    d1.Add_Process(p0);
    cout << d1 << endl;

    PCB *p1 = new PCB{1};
    p1->Add_Param("output.txt");
    p1->Add_Param("345");
    p1->Add_Param("W");
    p1->Add_Param("41");
    PCB *p2 = new PCB{2};
    p2->Add_Param("data.txt");
    p2->Add_Param("567");
    p2->Add_Param("R");
    p2->Add_Param("902");
    PCB *p3 = new PCB{3};
    p3->Add_Param("password.txt");
    p3->Add_Param("21");
    p3->Add_Param("W");
    p3->Add_Param("345");
    PCB *p4 = new PCB{4};
    p4->Add_Param("hash.txt");
    p4->Add_Param("987");
    p4->Add_Param("R");
    p4->Add_Param("75");

    d1.Add_Process(p2);
    d1.Add_Process(p1);
    d1.Add_Process(p4);
    d1.Add_Process(p3);
    cout << d1;
}
