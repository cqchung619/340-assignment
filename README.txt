Cuong Chung
CSCI 34000 – Assignment #2 README
Prof. Eric Schweitzer

This programm is a simulation of the basic handling of data structures in an OS.
Such data structures are the PCB (Process Control Block), Ready Queue, and Device Queues.

Compilation:
This program is written in the c++ programming language using standard c++11.

You can compile everything by typing into the command line:
> make all

Clean up:
You can clean up object and executable files by typing into the command line:
> make clean
This will delete all .o files and executables.

Running the Program:
The executable will be ~/temp/run.me. To run, type into the command line:
> ~/temp/run.me

Program Manual:
When the program starts, you will be prompted 3 times for the number of printers,
disks, and CD/RWs. Afterwards, the program will wait for an input.

Inputs:
Interrupts:
        A - Creates a new process and adds it to the ready queue.
        S - Snapshot. You will be asked for another input:
             r - Prints the PID of the processes in the ready queue.
             p - Prints the processes of every printer device queue.
             d - Prints the processes of every disk device queue
             c - Prints the processes of every CD/RW device queue
 (P/D/C)# - Any of the 3 letter and a number will indicate an interrupt. This signals the device
           has completed its task. The process in front of the device queue is moved to the back
           of the ready queue.

System Calls:
 (p/d/c)# - Any of the 3 letter and a number will indicate a system call. The process in
           front of the ready queue will be moved to the back of the indicated device queue.
        t - Terminates the current process in front of the ready queue. It's resources will be
           returned to the system.
EXIT/exit - Exits the program.
