/*
Author: Cuong Chung
Course: CSCI 34000
Instructor: Eric Schweitzer
Assignment #1: Basic data structures of OS
*/

#include "OS.h"
#include "Device.h"
#include "PCB.h"
using namespace std;


int main() {
    // OS system340;
    // system340.Run();

    Device d1{"printer1"};
    // cout << "Empty Device: " << endl << d1;
    cout << d1 << endl;;

    PCB p1{0};
    PCB p2{1};
    p1.Add_Param("input.txt");
    p1.Add_Param("3425");
    p1.Add_Param("W");
    p1.Add_Param("154");
    p2.Add_Param("input2.txt");
    p2.Add_Param("273");
    p2.Add_Param("W");
    p2.Add_Param("33");

    d1.Add_Process(p1);
    cout << d1 << endl;;
    d1.Add_Process(p2);
    cout << d1 << endl;;

    d1.Remove_Current_Process();
    cout << d1 << endl;;
    d1.Add_Process(p1);
    cout << d1 << endl;;
    d1.Add_Process(p1);
    cout << d1 << endl;;
    d1.Remove_Current_Process();
    cout << d1 << endl;;
    d1.Add_Process(p2);
    cout << d1 << endl;;
    d1.Add_Process(p2);
    cout << d1 << endl;;

    return 0;
}
