#include "SystemGenerator.h"

bool SystemGenerator::Is_Valid_Numeric_Input(const string &user_input) {
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
    Set_Memory(an_OS);

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
    cout << endl;

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
    cout << endl;

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
    cout << endl;

    an_OS.Initialize_CDs(stoi(number_of_devices));
}

void SystemGenerator::Set_Initial_CPU_Scheduling_Values(OS &an_OS) {
    string input = "";

    double alpha = 0;
    cout << "What is the history parameter alpha?\n> ";
    while (true) {
        getline(cin, input);

        istringstream double_stream{input};
        if ( (double_stream >> alpha) && (alpha >= 0) && (alpha <= 1) ) {
            break;
        }
        alpha = 0;

        cout << "Invalid input. Alpha should be a number within 0 and 1:\n> ";
    }
    an_OS.Set_History_Alpha(alpha);

    double tau = 0;
    cout << "What is the initial burst tau (in milliseconds)?\n> ";
    while (true) {
        getline(cin, input);

        istringstream double_stream{input};
        if ( (double_stream >> tau) && (tau > 0) ){
            break;
        }
        tau = 0;

        cout << "Invalid input. Tau should be a positive number:\n> ";
    }
    cout << endl;

    an_OS.Set_Initial_Burst_Tau(tau);
}

void SystemGenerator::Set_Memory(OS &an_OS) {
    string input = "";

    cout << "What is the size of memory?\n> ";
    getline(cin, input);
    while ( (!Is_Valid_Numeric_Input(input)) || (!Is_Power_Of_Two(input)) ) {
        cout << "Invalid input. Please enter a valid number that is a power of 2:\n> ";
        getline(cin, input);
    }
    int max_mem_size = stoi(input);
    // Add to OS.

    cout << "What is the max process size?\n> ";
    getline(cin, input);
    while ( (!Is_Valid_Numeric_Input(input) ) {
        cout << "Invalid input. Please enter a valid number up to " << max_mem_size << ":\n> ";
        getline(cin, input);
    }
}

bool SystemGenerator::Is_Power_Of_Two(const string &user_input) {
    int mem_size = stoi(user_input);
    if (mem_size == 0) {
        return false;
    }

    return ( (mem_size & (mem_size - 1)) == 0 );

}
