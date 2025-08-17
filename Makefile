CC = g++
LD = g++

CFLAGS += -Wall -Wpedantic

SOURCES := $(wildcard *.cpp)
OBJS := $(SOURCES:.cpp=.o)

all : a

a : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f *.o a
