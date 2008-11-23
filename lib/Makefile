-include ../Makefile.def

OBJS = pqueue.o queue.o test.o
LIB = libm3.a

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

.PHONY: clean

clean_impl:
	rm -f $(LIB) $(OBJS) $(OBJS:%.o=%.d)
