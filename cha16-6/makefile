CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/ 



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: async


async: $(OBJECTS)

	$(CC) $(OBJECTS) $(LFLAGS) -o async



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o async



rebuild: clean all

