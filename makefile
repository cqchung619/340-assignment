CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall

# Edit the following SOURCES variable to include all of the .cpp files to compile
SOURCES = main.cpp SystemGenerator.cpp OS.cpp CPU.cpp Device.cpp PCB.cpp PCBQueue.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE_NAME = ~/temp/run.me
EXECUTABLE_NAME2 = run

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

windows: $(EXECUTABLE_NAME2)

$(EXECUTABLE_NAME2): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME2) $(OBJECTS)

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME) $(EXECUTABLE_NAME2)
