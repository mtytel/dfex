CC=g++
EXEC=dfex
CFLAGS=-o $(EXEC) -g -Wall -O3 -lncurses -lm -lboost_thread-mt `pkg-config --cflags --libs jack`
COMPILE=$(CC) -o $(EXEC) -c -I lib/rapidxml-1.13/ -I /opt/local/include/
LDFLAGS=

OBJS := $(patsubst src/%.cpp,debug/src/%.o,$(wildcard src/*.cpp))

all: dfex

dfex: $(OBJS)
	@echo 'Building Executable: $@'
	@$(CC) $(OBJS) $(CFLAGS)
	@echo 'Complete'
	@echo ' '

debug/src/%.o: src/%.cpp
	@echo 'Building $@'
	@$(COMPILE) $< -o $@

clean:
	-$(RM) debug/src/*.o

