include ../Makefile.inc

LIB = libutil.a

SRC = strutils.c
OBJS = $(SRC:.c=.o)

TEST_SRC = $(SRC:.c=_test.c)
TEST_OBJS = $(TEST_SRC:.c=.o)
TEST_EXES =  $(TEST_SRC:.c=.exe)

.PHONY: default force tests runtests deps clean clobber

default: $(LIB)

force:
	true

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

strutils_test.exe: strutils_test.o strutils.o
	$(LD) $(LDFLAGS) $^ $(TEST_LDFLAGS) -o $@

tests: force
	$(MAKE) $(TEST_EXES)

runtests: tests
	for t in $(TEST_EXES); do (./$$t); done

deps:
	$(CC) -MM $(CFLAGS) $(SRC) $(TEST_SRC) > Makefile.deps

clean:
	rm -rf $(OBJS) $(TEST_OBJS)

clobber:
	rm -f $(OBJS) $(TEST_OBJS) $(TEST_EXES) $(LIB)

include Makefile.deps
