# Define directories
SRC_DIR = src
BIN_DIR = bin
DOC_DIR = doc

# Define the executable name
EXEC = cb

# Define compiler and flags
CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Default target
all: $(BIN_DIR)/$(EXEC)

# Build executable
$(BIN_DIR)/$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_DIR)/$(EXEC)

# Phony targets
.PHONY: all clean doc
