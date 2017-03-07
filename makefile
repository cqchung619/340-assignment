CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall

# Edit the following SOURCES variable to include all of the .cpp files to compile
SOURCES = main.cpp OS.cpp InterruptHandler.cpp Scheduler.cpp CPU.cpp PCB.cpp PCBQueue.cpp Device.cpp CD.cpp Printer.cpp Disk.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE_NAME = ~/temp/run.me

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)
