CC = g++
LD = g++

CFLAGS += -Wall -Wpedantic

all : a
	
a : main.o
	$(LD) $^ $(LDFLAGS) -o $@ $(LDLIBS)

main.o : main.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f *.o a
