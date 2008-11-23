-include ../Makefile.def

LIBS = ../lib/libm3.a
BINARY = libm3_test
OBJS = \
array_test.o\
main.o\
pqueue_test.o\
queue_test.o

ifneq (undefined, $(origin NOFORK))
CFLAGS := $(CFLAGS) -DT_NO_FORK
endif

all: $(BINARY)

$(BINARY): $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $(BINARY) $(OBJS) $(LIBS)

../lib/libm3.a:
	@make -C ../lib

-include *.d

.PHONY: clean_impl

clean_impl:
	@make -C ../lib clean
	rm -f $(OBJS) $(BINARY) $(OBJS:%.o=%.d)
