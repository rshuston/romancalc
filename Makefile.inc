UNAME := $(shell uname)

CC = gcc
CFLAGS = -g -Wall

LD = gcc
LDFLAGS =

AR = ar
ARFLAGS = rcs

ifeq ($(UNAME), Darwin)
CFLAGS += -I /opt/local/include
CHECK_TEST_LIBS = /opt/local/lib/libcheck.a
endif
ifeq ($(UNAME), Linux)
CHECK_TEST_LIBS = -lcheck -lsubunit -lm -lrt -lpthread
endif

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
