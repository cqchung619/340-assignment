#include "OS.h"

void OS::Initialize_Devices(const vector<unsigned int> &device_count) {
    unsigned int number_of_printers = device_count[0];
    unsigned int number_of_disks = device_count[1];
    unsigned int number_of_optical_drives = device_count[2];

    for (unsigned int i = 0; i < number_of_printers; ++i) {
        string name = "p" + to_string(i);
        Device *printer = new Device{name};
        device_table_["printers"].insert(std::pair<string, Device*>{name, printer});
    }

    for (unsigned int i = 0; i < number_of_disks; ++i) {
        string name = "d" + to_string(i);
        Device *disk = new Device{name};
        device_table_["disks"].insert(std::pair<string, Device*>{name, disk});
    }

    for (unsigned int i = 0; i < number_of_optical_drives; ++i) {
        string name = "c" + to_string(i);
        Device *optical_drive = new Device{name};
        device_table_["CD/RWs"].insert(std::pair<string, Device*>{name, optical_drive});
    }
}

bool OS::Is_Valid_Signal_Input(const string &an_input) {
    size_t input_length = an_input.length();
    bool is_valid = false;

    if (input_length == 1) { // A, S, t
        is_valid = an_input == "A" || an_input == "S" || an_input == "t";
    } else if (input_length == 2) { // (P/D/C)#, (p/d/c)#
        if (isalpha(an_input[0]) && isdigit(an_input[1])) { // (letter)(number)
            // true if an_input found, otherwise false (Device does not exist).
            if (isupper(an_input[0])) { // Device names start with lowercase letters.
                string temp = "";
                temp += tolower(an_input[0]);
                temp += an_input[1];
                for (auto table : device_table_) {
                    is_valid = (table.second.count(temp) != 0) ;
                }
            } else {
                for (auto table : device_table_) {
                    is_valid = (table.second.count(an_input) != 0) ;
                }
            }
        }
    } else if (an_input == "EXIT" || an_input == "exit") {
        is_valid = true;
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
    switch (an_input[0]) {
        case 'A':
            Create_Process();
            break;
        case 'S':
            Snapshot();
            break;
        case 'P':
            cout << "Device finished" << endl;
            break;
        case 'D':
            cout << "Device finished" << endl;
            break;
        case 'C':
            cout << "Device finished" << endl;
            break;
    }
}

void OS::Handle_Sys_Call(const string &an_input) {
    switch (an_input[0]) {
        case 't':
            if (!cpu_->Is_Idle() && !ready_queue_->empty()) {
                Terminate_Running_Process();
            } else {
                cout << "Error: No running process" << endl;
            }
            break;
        case 'p':
            cout << "Requesting Device" << endl;
            break;
        case 'd':
            cout << "Requesting Device" << endl;
            break;
        case 'c':
            cout << "Requesting Device" << endl;
            break;
    }
}

void OS::Create_Process() {
    PCB *new_process = new PCB(PID_counter_++);
    ready_queue_->enqueue(new_process);
    if (cpu_->Is_Idle()) {
        cpu_->Bind_Process(ready_queue_->front());
    }
}

void OS::Terminate_Running_Process() {
    cpu_->Unbind_Process();
    PCB *terminated_process = ready_queue_->dequeue();
    delete terminated_process;
    if (!ready_queue_->empty()) {
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

    switch (an_input[0]) {
        case 'r':
            cout << "---Ready Queue---" << endl;
            cout << right
                 << setw(5) << "PID" << endl;
            ready_queue_->Output_Processes(cout, PCB::CPU);
            break;
        case 'p':
            cout << right
                 << setw(5) << "PID"
                 << setw(20) << "FILENAME"
                 << setw(10) << "MEMSTART"
                 << setw(5) << "R/W"
                 << setw(20) << "FILE_LENGTH" << endl;

            for (auto printer : device_table_["printers"]) {
                cout << *(printer.second) << endl;
            }
            break;
        case 'd':
            cout << right
                << setw(5) << "PID"
                << setw(20) << "FILENAME"
                << setw(10) << "MEMSTART"
                << setw(5) << "R/W"
                << setw(20) << "FILE_LENGTH" << endl;

            for (auto disk : device_table_["disks"]) {
                cout << *(disk.second) << endl;
            }
            break;
        case 'c':
            cout << right
                << setw(5) << "PID"
                << setw(20) << "FILENAME"
                << setw(10) << "MEMSTART"
                << setw(5) << "R/W"
                << setw(20) << "FILE_LENGTH" << endl;

            for (auto optical_drive : device_table_["CD/RWs"]) {
                cout << *(optical_drive.second) << endl;
            }
            break;
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
            cout << "Invalid\n";
        }
    }
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
