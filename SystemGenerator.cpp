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
    cin.clear();
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
    double input = 0;

    cout << "What is the history parameter alpha?\n> ";
    cin >> input;
    while ( (!cin.good()) || (input < 0) || (input > 1)) {
        cout << "Invalid input. Alpha should be a number within 0 and 1:\n> ";
        cin.clear();
        cin.ignore(100000, '\n');
        cin >> input;
    }
    an_OS.Set_History_Alpha( input);

    cout << "What is the initial burst tau (in milliseconds)?\n> ";
    cin >> input;
    while ( !cin.good() ) {
        cout << "Invalid input. Tau should be a positive number:\n> ";
        cin.clear();
        cin.ignore(100000, '\n');
        cin >> input;
    }
    an_OS.Set_Initial_Burst_Tau(input);
}
