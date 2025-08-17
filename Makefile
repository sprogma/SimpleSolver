CC = g++
LD = g++

CFLAGS += -Wall -Wpedantic

SOURCES := $(wildcard *.cpp)

all : a
	
a : $(SOURCES)
	$(LD) $^ $(LDFLAGS) -o $@

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f *.o a
