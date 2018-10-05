ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "solaris"
  EXTRALIBS = -lsocket -lnsl
endif

PROGS =  ruptimed

all:	$(PROGS) $(MOREPROGS) clconn.o clconn2.o initsrv1.o initsrv2.o 

%:	%.c $(LIBAPUE)


ruptimed:	ruptimed.o initsrv2.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o ruptimed ruptimed.o initsrv2.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o

include $(ROOT)/Make.libapue.inc
