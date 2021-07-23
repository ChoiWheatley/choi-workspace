.SUFFIXES:%.c %.h

INC=-I.
DEBUG= -g -DDBG
CFLAGS=$(INC) $(DEBUG) -Wall -Werror -pthread
LINK+=-lrt
CC=gcc-10 

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
TARGET=$(OBJS:.o=.out)

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $(patsubst %.out,%.o,$@) $(LINK)
#	@for i in $(TARGET); \
#		do \
#			echo $(CC) -o $$i $(patsubst %.out,%.o, $$i); \
#		done

clean:
	$(RM) $(TARGET) $(OBJS) *.out *.o

