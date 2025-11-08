CC      = clang++
CFLAGS  = -std=c++17 -Wall -O2
LFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

BINARY  = bin/smarttalesii
SRC_DIR = smart_tales_ii

CPPS = $(shell find $(SRC_DIR) -name *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(CPPS))
# Gcc/Clang will create these .d files containing dependencies.
DEPS = $(patsubst %.cpp, %.d, $(CPPS))

.PHONY: all check syntax clean format

all: $(BINARY)

check: $(BINARY)
	cd bin && ./smarttalesii debug

syntax: $(CPPS)
	$(CC) -fsyntax-only $(CPPS)
	
clean:
	-rm $(OBJS)
	-rm $(DEPS)
	-rm $(BINARY)

format:
	clang-format -i ${CPPS}
	clang-format -i $(shell find ${SRC_DIR} -name '*.hpp')

-include $(DEPS)

%.o: %.cpp
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Actual target of the binary - depends on all .o files.
# The @D you're seeing here and elsewhere simply means the directory of the file
# we're making.
$(BINARY): $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(BINARY)
