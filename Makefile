# Makefile for Chamber Control System

# NetBurner specific configuration
NBURN_ROOT = /opt/netburner/sdk	 # NetBurner SDK root directory (This is invalid here)
include $(NBURN_ROOT)/make/common.mak

# Project name
PROJECT = ChamberControlSystem

# Output directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Source directories
SRC_DIR = src
INC_DIR = inc 

# Collect all source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
		  $(wildcard $(SRC_DIR)/Hardware/*.cpp) \	
		  $(wildcard $(SRC_DIR)/Control/*.cpp) \	
		  $(wildcard $(SRC_DIR)/Communication/*.cpp)

# Generate object file names
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Include paths
INCLUDES = -I$(INC_DIR) \
		   -I$(NBURN_ROOT)/include \
		   -I$(NBURN_ROOT)/include/predef

# Compiler flags
CXXFLAGS += -Wall -Wextra -Werror -02 $(INCLUDES) -std=c++11

# Linker flags
LDFLAGS += -L$(NBURN_ROOT)/lib 

# Default target
all: directories $(BIN_DIR)/$(PROJECT).s19

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/Hardware
	@mkdir -p $(OBJ_DIR)/Control
	@mkdir -p $(OBJ_DIR)/Communication
	@mkdir -p $(BIN_DIR)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the project
$(BIN_DIR)/$(PROJECT).s19: $(OBJECTS)
	@echo "Linking $(PROJECT)..."
	@$(CXX) $(OBJECTS) $(LDFLAGS) -o $(BIN_DIR)/$(PROJECT).elf 
	@$(OBJCOPY) -O srec $(BIN_DIR)/$(PROJECT).elf $(BIN_DIR)/$(PROJECT).s19

# Clean build files
clean:
	@echo "Cleaning up build files..."
	@rm -rf $(BUILD_DIR)

# Flash target for uploading to device
flash: $(BIN_DIR)/$(PROJECT).s19
	@echo "Flashing device..."
	@$(NBURN_ROOT)/bin/nbflash -d /dev/ttyUSB0 $(BIN_DIR)/$(PROJECT).s19

# Debug target
debug: CXXFLAGS += -DDEBUG -g 
debug: all

# Release target
release: CXXFLAGS += -DNDEBUG 
release: all

# Help target
help:
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "  all       - Build the project"
	@echo "  directories - Create necessary directories"
	@echo "  clean     - Clean build files"
	@echo "  flash     - Flash the device"
	@echo "  debug     - Build with debugging information"
	@echo "  release   - Build without debugging information"

# Phony targets
.PHONY: all directories clean flash debug release help
