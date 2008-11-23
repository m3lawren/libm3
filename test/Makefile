CC = gcc
CFLAGS = -W -g -Wall -pedantic -I../include -MMD 
OBJS = main.o array_test.o pqueue_test.o queue_test.o
LIBS = ../lib/libm3.a
BINARY = libm3_test

ifneq (undefined, $(origin NOFORK))
CFLAGS := $(CFLAGS) -DT_NO_FORK
endif

all: $(BINARY)

$(BINARY): $(OBJS) $(LIBS)
	$(CC) -g -o $(BINARY) $(OBJS) $(LIBS)

../lib/libm3.a:
	@make -C ../lib

-include *.d

.PHONY: clean

clean:
	@make -C ../lib clean
	rm -f $(OBJS) $(BINARY) $(OBJS:%.o=%.d)
