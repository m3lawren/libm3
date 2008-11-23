-include ../Makefile.def

OBJS = pqueue.o queue.o test.o
LIB = libm3.a

default: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(LIB) $(OBJS)

.PHONY: clean

clean:
	rm -f $(LIB) $(OBJS) $(OBJS:%.o=%.d)
