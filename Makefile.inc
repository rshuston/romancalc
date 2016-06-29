UNAME = $(shell uname)

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
UNAME_VER = $(shell lsb_release -rs)
ifeq ($(UNAME_VER), 16.04)
CHECK_TEST_LIBS = -lcheck -lsubunit -lm -lrt -lpthread
else
CHECK_TEST_LIBS = -lcheck -lm -lrt -lpthread
endif
endif

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

