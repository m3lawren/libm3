CC = gcc
CFLAGS = -g -W -Wall -ansi -pedantic -I../include -MD
AR = ar rs
OBJS = array.o pqueue.o queue.o test.o
LIB = libm3.a

default: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

.PHONY: clean

-include *.d

clean:
	rm -f $(LIB) $(OBJS) $(OBJS:%.o=%.d)
