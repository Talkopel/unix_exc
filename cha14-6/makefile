CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/ -Lsync -llck



SOURCES = $(wildcard *.c)

OBJECTS = $(SOURCES:.c=.o)


all: lock_test


lock_test: $(OBJECTS)

	$(CC) $(OBJECTS) $(LFLAGS) -o lock_test



%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o lock_test



rebuild: clean all

