# Compiler and archiver
CXX = clang++
AR = ar
CXXFLAGS = -Wall -Wpedantic -Werror -std=c++20 -g

# Directory structure
SRC_ROOT := Src
BUILD_ROOT := Build
EXTERNAL := External

# Get all subdirectories in Src and External
SRC_DIRS := $(shell find $(SRC_ROOT) -type d)
EXT_DIRS := $(EXTERNAL)/

# Include paths
INCLUDES := $(addprefix -I, $(SRC_DIRS) $(EXT_DIRS))

# All .cpp files except main
LIB_SRCS := $(filter-out $(SRC_ROOT)/Main/Main.cpp, $(shell find $(SRC_ROOT) -name '*.cpp'))
LIB_OBJS := $(patsubst $(SRC_ROOT)/%.cpp, $(BUILD_ROOT)/%.o, $(LIB_SRCS))

# Main source and object
MAIN_SRC := $(SRC_ROOT)/Main/Main.cpp
MAIN_OBJ := $(patsubst $(SRC_ROOT)/%.cpp, $(BUILD_ROOT)/%.o, $(MAIN_SRC))
MAIN_EXE := $(BUILD_ROOT)/Main/Main

# Output library
LIBRARY := $(BUILD_ROOT)/libproject.a

# Default target
all: $(MAIN_EXE)

# Link executable
$(MAIN_EXE): $(LIBRARY) $(MAIN_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Build static library
$(LIBRARY): $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

# Compile all .cpp to .o
$(BUILD_ROOT)/%.o: $(SRC_ROOT)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_ROOT)

.PHONY: all clean

run: 
	./$(MAIN_EXE)