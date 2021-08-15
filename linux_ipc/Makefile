.SUFFIXES:%.c %.h

CURDIR= $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
UTIL_DIR:=$(CURDIR)../util/
INC:=-I. -I$(UTIL_DIR)
DEBUG= -g -DDBG
CFLAGS=$(INC) $(DEBUG) -Wall -Werror -pthread
LINK+=-lrt -lpthread
CC=gcc-10 

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(OBJS:.o=.d)
TARGET=$(OBJS:.o=.out)

.PHONY: all
all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $(patsubst %.out,%.o,$@) $(LINK) -MD

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) *.out *.o

-include: $(DEPS)
