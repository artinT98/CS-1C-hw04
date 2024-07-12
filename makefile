# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Targets
TARGET = hw04
OBJECTS = hw04.o hw04f.o

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile main file
hw04.o: hw04.cpp hw04.h
	$(CXX) $(CXXFLAGS) -c hw04.cpp

# Compile function file
hw04f.o: hw04f.cpp hw04.h
	$(CXX) $(CXXFLAGS) -c hw04f.cpp

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Phony targets
.PHONY: all clean
