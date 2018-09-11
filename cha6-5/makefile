CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -c -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: date


date: $(OBJECTS)

	$(CC) $(OBJECTS) $(CFLAGS) -o date



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o date



rebuild: clean all

