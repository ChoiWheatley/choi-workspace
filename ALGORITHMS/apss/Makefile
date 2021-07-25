.SUFFIXES:%.c %.cpp %.h

INC=-I.

ifeq ($(RELEASE), 1)
	DEBUG=-O2 -DNDBG
else
	DEBUG=-g -O0 -DDBG
endif

CFLAGS=$(INC) $(DEBUG) -std=c++17 -Wall -pthread
CC=g++-10 

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
TARGET=$(OBJS:.o=.out)

all: $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $(patsubst %.out,%.o,$@)


clean:
	$(RM) $(TARGET) $(OBJS) *.out *.o

