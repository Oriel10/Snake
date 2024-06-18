# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Executable name
TARGET = SnakeGame.exe

# Directories
BUILD_DIR = build

# Source files
SRCS = main.cpp Snake.cpp SnakeGame.cpp

# Object files in the build directory
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Default rule to build the target executable
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo Build complete
	@echo Executable name - $(TARGET).


# Ensure the build directory exists
$(BUILD_DIR):
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Rules to compile each source file into an object file with dependencies
$(BUILD_DIR)/main.o: main.cpp SnakeGame.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

$(BUILD_DIR)/Snake.o: Snake.cpp Snake.hpp Common.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c Snake.cpp -o $@

$(BUILD_DIR)/SnakeGame.o: SnakeGame.cpp SnakeGame.hpp Snake.hpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c SnakeGame.cpp -o $@

# Rule to clean the build artifacts
clean:
	@if exist $(BUILD_DIR) del /Q $(BUILD_DIR)\*.o
	@if exist $(TARGET) del /Q $(TARGET)
	@if exist $(BUILD_DIR) rmdir /Q /S $(BUILD_DIR)

# Phony targets
.PHONY: all clean
