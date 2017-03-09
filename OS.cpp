#include "OS.h"

void OS::Initialize_Devices(const vector<unsigned int> &number_of_devices) {
    for (auto elem : number_of_devices) {
        cout << elem << endl;
    }
}

void OS::Run() {
    running = true;

    while (running) {
        cout << "> ";
        string input = "";
        getline(cin, input);

        if (Is_Valid_Input(input)) {
            Handle_Input(input);
        } else {
            cout << "Invalid\n";
        }
    }
}

bool OS::Is_Valid_Input(const string &an_input) {
    size_t input_length = an_input.length();
    bool is_valid = false;
    if (input_length == 1) {
        is_valid = an_input == "A" || an_input == "S";
    } else if (input_length == 2) {
        is_valid = true;
    } else if (an_input == "EXIT") {
        is_valid = true;
    }

    return is_valid;
}

void OS::Handle_Input(const string &an_input) {
    if (an_input == "EXIT") {
        running = false;
    }

    Device d1{"printer 1"};
    // CPU d1;
    PCB p1{0};
    p1.Add_Param("input.txt");
    p1.Add_Param("132");
    p1.Add_Param("W");
    p1.Add_Param("31");

    cout << d1 << endl;
    d1.Add_Process(p1);
    cout << d1 << endl;

    PCB p2{2};
    PCB p3{3};
    PCB p4{4};
    PCB p5{5};
    // d1.Add_Process(p3);
    // d1.Add_Process(p2);
    // d1.Add_Process(p5);
    // d1.Add_Process(p4);
    cout << d1;
}
