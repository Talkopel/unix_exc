CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -c -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: avl


avl: $(OBJECTS)

	$(CC) $(OBJECTS) $(CFLAGS) -o avl



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o avl



rebuild: clean all

