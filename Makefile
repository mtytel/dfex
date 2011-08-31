
CC=g++
EXEC=dfex
CFLAGS=-o $(EXEC) -g -O3 -lncurses `pkg-config --cflags --libs jack` -I "lib/rapidxml-1.13/"
COMPILE=$(CC) $(CFLAGS) -c
LDFLAGS=

OBJS := $(patsubst src/%.cpp,debug/src/%.o,$(wildcard src/*.cpp))

all: dfex

dfex: $(OBJS)
	@echo 'Building Executable: $@'
	@echo $(CC) $(CFLAGS) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS)
	@echo 'Complete'
	@echo ' '

debug/src/%.o: src/%.cpp
	@echo 'Building $@'
	$(COMPILE) $< -o $@
	@echo ' '

clean:
	-$(RM) debug/src/*.o

