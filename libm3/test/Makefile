CC = gcc
CFLAGS = -W -g -Wall -pedantic -I../include -MMD 
OBJS = pqueue_test.o main.o test.o
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
