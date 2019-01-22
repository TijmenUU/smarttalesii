CC     = g++
CFLAGS = -std=c++17 -Wall -O2
LFLAGS = -Wall
LIBS   = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

# Final binary
BIN       = bin/smarttalesii
# Put all auto generated stuff to this build dir.
BUILD_DIR = build
# Specify where to find the source files
SRC_DIR   = smart_tales_ii

# List of all .cpp source files.
CPP = $(wildcard $(SRC_DIR)/*.cpp)

# All .o files go to build dir.
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP))
# Gcc/Clang will create these .d files containing dependencies.
DEP = $(patsubst %.o, %.d, $(OBJ))

.PHONY: all check syntax clean

all: $(BIN)

check: $(BIN)
	cd bin && ./smarttalesii debug

syntax: $(CPP)
	$(CC) -fsyntax-only $(CPP)
	
clean:
	-rm -rf $(BUILD_DIR)
	-rm $(BIN)

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
# The @D you're seeing here and elsewhere simply means the directory of the file
# we're making.
$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Actual target of the binary - depends on all .o files.
$(BIN): $(OBJ)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LIBS) -o $(BIN)
