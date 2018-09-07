CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -c -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: cp2


cp2: $(OBJECTS)

	$(CC) $(OBJECTS) $(CFLAGS) -o cp2



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o cp2



rebuild: clean all

