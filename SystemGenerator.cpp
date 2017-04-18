#include "SystemGenerator.h"

bool SystemGenerator::Is_Valid_Numeric_Input(const string& user_input) {
    if (user_input == "") {
        return false;
    }

    for (unsigned int i = 0; i < user_input.length(); i++) {
        if (!isdigit(user_input[i])) {
            return false;
        }
    }

    return true;
}

OS SystemGenerator::Generate_OS() {
    OS an_OS{};
    cout << "System Installation: " << endl;

    Generate_Printers(an_OS);
    Generate_Disks(an_OS);
    Generate_CDs(an_OS);

    Set_Initial_CPU_Scheduling_Values(an_OS);

    cout << "System installed.\n" << endl;
    return an_OS;
}

void SystemGenerator::Generate_Printers(OS &an_OS) {
    string number_of_devices = "";

    cout << "How many printers will be installed?\n> ";
    getline(cin, number_of_devices);
    while (!Is_Valid_Numeric_Input(number_of_devices)) {
        cout << "Invalid input. Please enter a valid number:\n> ";
        getline(cin, number_of_devices);
    }

    an_OS.Initialize_Printers(stoi(number_of_devices));
}

void SystemGenerator::Generate_Disks(OS &an_OS) {
    string number_of_devices = "";

    // Number of disks.
    cout << "How many disks will be installed?\n> ";
    getline(cin, number_of_devices);
    while (!Is_Valid_Numeric_Input(number_of_devices)) {
        cout << "Invalid input. Please enter a valid number:\n> ";
        getline(cin, number_of_devices);
    }

    // Number of cylinders per disk.
    vector<unsigned int> disk_cylinder_count( (unsigned int) stoi(number_of_devices) );
    for (size_t i = 0; i < disk_cylinder_count.size(); ++i) {
        string number_of_cylinders = "";

        cout << "How many cylinders does disk "<< i << " have?\n> ";
        getline(cin, number_of_cylinders);
        while (!Is_Valid_Numeric_Input(number_of_cylinders)) {
            cout << "Invalid input. Please enter a valid number:\n> ";
            getline(cin, number_of_cylinders);
        }

        disk_cylinder_count[i] = (unsigned int) stoi(number_of_cylinders);
    }

    an_OS.Initialize_Disks(disk_cylinder_count);
}

void SystemGenerator::Generate_CDs(OS &an_OS) {
    string number_of_devices = "";

    cout << "How many CD/RWs will be installed?\n> ";
    getline(cin, number_of_devices);
    while (!Is_Valid_Numeric_Input(number_of_devices)) {
        cout << "Invalid input. Please enter a valid number:\n> ";
        getline(cin, number_of_devices);
    }

    an_OS.Initialize_CDs(stoi(number_of_devices));
}

void SystemGenerator::Set_Initial_CPU_Scheduling_Values(OS &an_OS) {
    string input = "";

    cout << "What is the history parameter alpha?\n> ";
    getline(cin, input);
    // Short-circuiting: Right side is evaluated only if input is a valid numeric input.
    // O <= alpha <= 1
    while ( !Is_Valid_Numeric_Input(input) || ((double) stoi(input) > 1) ) {
        cout << "Invalid input. Alpha should be a number within 0 and 1:\n> ";
        getline(cin, input);
    }
    an_OS.Set_History_Alpha( (double) stoi(input) );

    cout << "What is the initial burst tau (in milliseconds)?\n> ";
    getline(cin, input);
    // Short-circuiting: Right side is evaluated only if input is a valid numeric input.
    // O <= alpha <= 1
    while ( !Is_Valid_Numeric_Input(input) ) {
        cout << "Invalid input. Tau should be a positive number:\n> ";
        getline(cin, input);
    }
    an_OS.Set_Burst_Tau( (double) stoi(input) );
}
