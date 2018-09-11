CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -c -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: dirlim


dirlim: $(OBJECTS)

	$(CC) $(OBJECTS) $(CFLAGS) -o dirlim



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o dirlim



rebuild: clean all

