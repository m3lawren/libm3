-include ../Makefile.def

OBJS = \
array.o\
pqueue.o\
queue.o\
test.o
LIB = libm3.a

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

.PHONY: clean

-include *.d

clean_impl:
	rm -f $(LIB) $(OBJS) $(OBJS:%.o=%.d)
