CC = g++
AR = ar
SRC_ROOT = Src
BUILD_ROOT = Build
SRC_DIRS := $(shell find $(SRC_ROOT) -type d)
CFLAGS = -Wall -Wpedantic -Werror -std=c++20 $(addprefix -I, $(SRC_DIRS))

# All .cpp files
SRCS := $(shell find $(SRC_ROOT) -name '*.cpp')

# Object files: Src/foo/bar.cpp → Build/foo/bar.o
OBJS := $(patsubst $(SRC_ROOT)/%.cpp, $(BUILD_ROOT)/%.o, $(SRCS))

# Main file and output
MAIN_OBJ := $(BUILD_ROOT)/Main/Main.o
MAIN_EXE := $(BUILD_ROOT)/Main/Main
LIB := $(BUILD_ROOT)/library.a

all: $(BUILD_ROOT) $(LIB) $(MAIN_EXE)

# Create Build/ directories recursively
$(BUILD_ROOT):
	mkdir -p $(addprefix $(BUILD_ROOT)/, $(shell find $(SRC_ROOT) -type d | sed "s|^$(SRC_ROOT)/||"))

# Compile each .cpp file to .o
$(BUILD_ROOT)/%.o: $(SRC_ROOT)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Static library of everything except Main
$(LIB): $(filter-out $(MAIN_OBJ), $(OBJS))
	$(AR) rcs $@ $^

# Link Main.o + lib to make final binary
$(MAIN_EXE): $(MAIN_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

run: $(MAIN_EXE)
	./$(MAIN_EXE)

clean:
	rm -rf $(BUILD_ROOT)
