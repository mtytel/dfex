
CC=g++
EXEC=dfex
CFLAGS=-o $(EXEC) -O3 -lncurses `pkg-config --cflags --libs jack`
COMPILE=$(CC) $(CFLAGS) -c
LDFLAGS=

OBJS := $(patsubst src/%.cpp,debug/src/%.o,$(wildcard src/*.cpp))

all: clean dfex

dfex: $(OBJS)
	@echo 'Building Effects Pedal: $@'
	@echo $(CC) $(CFLAGS) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS)
	@echo 'Complete'
	@echo ' '

debug/src/%.o: src/%.cpp
	@echo 'Building $@'
	$(COMPILE) $< -o $@
	@echo 'Done'

clean:
	-$(RM) debug/src/*.o

