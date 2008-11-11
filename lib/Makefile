CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -I../include
AR = ar rs
LIBPQUEUE_OBJS = pqueue.o
LIBPQUEUE_LIB = libpqueue.a
ALL_LIBS = $(LIBPQUEUE_LIB)

default: $(ALL_LIBS)

$(LIBPQUEUE_LIB): $(LIBPQUEUE_OBJS)
	$(AR) $(LIBPQUEUE_LIB) $(LIBPQUEUE_OBJS)

.PHONY: clean

clean:
	rm -f $(LIBPQUEUE_OBJS) $(LIBPQUEUE_LIB) $(LIBPQUEUE_OBJS:%.o=%.d)
