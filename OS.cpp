#include "OS.h"

void OS::Run() {
    running = true;

    while (running) {
        cout << ">";
        string input = "";
        getline(cin, input);

        if (input == "shutdown") {
            running = false;
        }
    }
}
