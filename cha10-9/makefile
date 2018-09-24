CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -c -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: iter


iter: $(OBJECTS)

	$(CC) $(OBJECTS) $(CFLAGS) -o iter



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o iter



rebuild: clean all

