CC = gcc

LD = gcc



CFLAGS = -g

OFLAGS = -c -I/usr/include

LFLAGS = $(CFLAGS) -L/usr/lib/



SRSOURCES = lib.c serv.c

SROBJECTS = $(SRSOURCES:.c=.o)

CLSOURCES = lib.c client.c

CLOBJECTS = $(CLSOURCES:.c=.o)

all: serv client


serv: $(SROBJECTS)

	$(CC) $(SROBJECTS) $(CFLAGS) -o serv

client: $(CLOBJECTS)
	
	$(CC) $(CLOBJECTS) $(CFLAGS) -o client


%.o: %.c

	$(CC) $(CFLAGS) -c $< -o $@



clean:

	rm -rf *.o serv client



rebuild: clean all

