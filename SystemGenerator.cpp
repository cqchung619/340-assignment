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
    vector<unsigned int> device_count;
    cout << "System Installation: " << endl;

    string number_of_device = "";

    // Printers generation.
    cout << "How many printers will be installed?\n> ";
    getline(cin, number_of_device);
    while (!Is_Valid_Numeric_Input(number_of_device)) {
        cout << "Invalid input. Please enter a valid number:\n> ";
        getline(cin, number_of_device);
    }
    device_count.push_back(stoi(number_of_device));

    // Disks generation.
    cout << "How many disks will be installed?\n> ";
    getline(cin, number_of_device);
    while (!Is_Valid_Numeric_Input(number_of_device)) {
        cout << "Invalid input. Please enter a valid number:\n> ";
        getline(cin, number_of_device);
    }
    device_count.push_back(stoi(number_of_device));

    // CD/RWs generation.
    cout << "How many CD/RWs will be installed?\n> ";
    getline(cin, number_of_device);
    while (!Is_Valid_Numeric_Input(number_of_device)) {
        cout << "Invalid input. Please enter a valid number:\n> ";
        getline(cin, number_of_device);
    }
    device_count.push_back(stoi(number_of_device));

    OS an_OS{};
    an_OS.Initialize_Devices(device_count);

    return an_OS;
}
