CC = clang++-6.0
CFLAGS = -std=c++14 -Wall -O3
LFLAGS = -Wall
LIBS = -lm -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

# Final binary
BIN = ../bin/smarttalesii
# Put all auto generated stuff to this build dir.
BUILD_DIR = ./build

# List of all .cpp source files.
CPP = $(wildcard ./*.cpp)

# All .o files go to build dir.
OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Actual target of the binary - depends on all .o files.
$(BIN) : $(OBJ)
	mkdir -p $(@D)
	$(CC) $(LFLAGS) $(OBJ) $(LIBS) -o $(BIN)

.PHONY: all
all: $(BIN)

.PHONY: syntax
syntax: $(CPP)
	$(CC) -fsyntax-only $(CPP)

.PHONY: clean
clean:
	-rm $(BIN) $(OBJ) $(DEP) 2> /dev/null
