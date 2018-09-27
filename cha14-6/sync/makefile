CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -g # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = liblck.so # target lib
AR = ar
ARFLAGS = rcs 

SRCS = sync.c # source files
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(AR) $(ARFLAGS) liblck.a $(SRCS:.c=.o)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)

