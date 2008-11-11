CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -I../include -MD
AR = ar rs
OBJS = pqueue.o
LIB = libm3.a

default: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

.PHONY: clean

clean:
	rm -f $(LIB) $(OBJS) $(OBJS:%.o=%.d)
