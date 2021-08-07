tab:=⠀    #
define newline


endef

# MAKEFILE_LIST 변수는 가장 최근에 수행한 makefile의 이름을 저장한다.
# 초기값은 현재 이 메이크파일의 이름이 저장되어있을 것이고, 
# 
CURDIR:= $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
INC:=-I$(CURDIR)

ifeq ($(RELEASE), 1)
	DEBUG=-O2 -DNDBG
else
	DEBUG=-g -O0 -DDBG
endif

CFLAGS:=$(INC) $(DEBUG) -std=c++17 -Wall -pthread
CC=g++-10 
LDFLAGS=-lrt

$(info $(tab)start ...$(newline))
$(info $(tab)current directory=$(CURDIR))

SRCS:=$(wildcard *.cpp)
OBJS:=$(SRCS:.cpp=.o)
TARGET:=$(SRCS:.cpp=.out)
DEPS=$(OBJS:.o=.d)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo $(tab)making binaries...
#	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(patsubst %.out, %.o, $@)
	$(CC) $(CFLAGS) $(patsubst %.out, %.o, $@) -o $@

%.o: %.cpp
	@echo making object files...
	$(CC) $(CFLAGS) $(LDFLAGS) -MD -c $< -o $@


.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
