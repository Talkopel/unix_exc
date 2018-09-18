ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
	ZAP = zap
else
	ZAP =
endif


#PROGS =	access cdpwd changemod devrdev filetype mycd umask unlink $(ZAP)
MOREPROGS = waitid

all:	$(PROGS) $(MOREPROGS)

%:	%.c $(LIBAPUE)
	$(CC) -g -Wmaybe-uninitalized -Wdiv-by-zero $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

waitid:	waitid.c $(LIBAPUE)
	$(CC) -g $(CFLAGS) $(NAMEMAX) waitid.c -o waitid $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ZAP)

include $(ROOT)/Make.libapue.inc
