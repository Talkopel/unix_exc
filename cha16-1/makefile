CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/ 



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: byteorder


byteorder: $(OBJECTS)

	$(CC) $(OBJECTS) $(LFLAGS) -o byteorder



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o byteorder



rebuild: clean all

