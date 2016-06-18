UNAME := $(shell uname)

CC = gcc
CFLAGS = -g -Wall

LD = gcc
LDFLAGS =

AR = ar
ARFLAGS = rcs

ifeq ($(UNAME), Darwin)
CHECK_TEST_LIBS = /opt/local/lib/libcheck.a
endif
ifeq ($(UNAME), Linux)
CHECK_TEST_LIBS = -lcheck -lsubunit -lm -lrt -lpthread
endif

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
