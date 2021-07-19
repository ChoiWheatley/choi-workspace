.SUFFIXES:%.c %.cpp %.h

INC=-I.
DEBUG= -g -DDBG
CFLAGS=$(INC) -std=c++17 -Wall -pthread
CC=g++-10 

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
TARGET=$(OBJS:.o=.out)

all: $(TARGET)
	$(RM) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(CC) -o $@ $(patsubst %.out,%.o,$@)

clean:
	$(RM) $(TARGET) $(OBJS) *.out *.o

