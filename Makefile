
CC=g++
CFLAGS=-o Digifex -O3 `pkg-config --cflags --libs jack`
COMPILE=$(CC) $(CFLAGS) -c
LDFLAGS=

OBJS := $(patsubst src/%.cpp,src/%.o,$(wildcard src/*.cpp))

all: Digifex

Digifex: $(OBJS)
	@echo 'Building Effects Pedal: $@'
	@echo $(CC) $(CFLAGS) $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS)
	@echo 'Complete'
	@echo ' '

%.o: %.cpp
	@echo 'Building $@'
	$(COMPILE) $< -o $@
	@echo 'Done'

clean:
	-$(RM) src/*.o Digifex

