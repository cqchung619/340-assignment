#include "OS.h"

void OS::Initialize_Devices(const vector<unsigned int> &device_count) {
    unsigned int number_of_printers = device_count[0];
    unsigned int number_of_disks = device_count[1];
    unsigned int number_of_optical_drives = device_count[2];

    for (unsigned int i = 0; i < number_of_printers; ++i) {
        string name = "p" + to_string(i);
        Device *printer = new Device{name};
        device_table_.insert(std::pair<string, Device*>{name, printer});
    }

    for (unsigned int i = 0; i < number_of_disks; ++i) {
        string name = "d" + to_string(i);
        Device *disk = new Device{name};
        device_table_.insert(std::pair<string, Device*>{name, disk});
    }

    for (unsigned int i = 0; i < number_of_optical_drives; ++i) {
        string name = "c" + to_string(i);
        Device *optical_drive = new Device{name};
        device_table_.insert(std::pair<string, Device*>{name, optical_drive});
    }

    cout << left
        << setw(5) << "PID"
        << setw(20) << "FILENAME"
        << setw(10) << "MEMSTART"
        << setw(5) << "R/W"
        << setw(20) << "FILE_LENGTH" << endl;

    for (auto it = device_table_.begin(); it != device_table_.end(); ++it) {
        cout << *(it->second) << endl;
    }
}

bool OS::Is_Valid_Signal_Input(const string &an_input) {
    size_t input_length = an_input.length();
    bool is_valid = false;

    if (input_length == 1) { // A, S, t
        is_valid = an_input == "A" || an_input == "S" || an_input == "t";
    } else if (input_length == 2) { // (P/C/D)#, (p/c/d)#
        if (isalpha(an_input[0]) && isdigit(an_input[1])) { // (letter)(number)
            // true if an_input found, otherwise false (Device does not exist).
            is_valid = (device_table_.find(an_input) != device_table_.end() ) ;
        }
    } else if (an_input == "EXIT" || an_input == "exit") {
        is_valid = true;
    }

    return is_valid;
}

void OS::Process_Input(const string &an_input) {
    switch (an_input.length()) {
        case 1:
            if (isupper(an_input)) {
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

void Handle_Interrupt(const string *an_input) {
    switch ((char) an_input) {
        case 'A':
            break;
        case 'S':
            

            break;
        case 't':
            break;
    }
}

void Handle_Sys_Call(const string &an_input) {

}

void OS::Run() {
    while (running_) {
        cout << "> ";
        string input = "";
        getline(cin, input);

        if (Is_Valid_Signal_Input(input)) {
            Handle_Input(input);
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
