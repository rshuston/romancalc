include ../Makefile.inc

LIB = libutil.a

SRC = strutils.c
OBJS = $(SRC:.c=.o)

TEST_SRC = $(SRC:.c=_test.c)
TEST_OBJS = $(TEST_SRC:.c=.o)
TEST_EXES =  $(TEST_SRC:.c=.exe)

.PHONY: default force tests runtests clean clobber

default: $(LIB)

force:
	true

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

tests: force
	$(MAKE) $(TEST_EXES)

runtests: tests
	for t in $(TEST_EXES); do (./$$t); done

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TEST_OBJS) $(TEST_OBJS:.o=.d)

clobber:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TEST_OBJS) $(TEST_OBJS:.o=.d)
	rm -f $(TEST_EXES) $(LIB)

-include $(wildcard *.d)
