.SUFFIXES: %.o %.c %.h

INC:=-I. $(SRCDIRS)/.
OBJDIRS= ./objs
SRCDIRS= ./6_brute_force ./7_divide_and_conquer ./8_dynamic_programming

ifeq ($(RELEASE), 1)
	DEBUG=-O2 -DNDBG
else
	DEBUG=-g -O0 -DDBG
endif

CFLAGS:=$(INC) $(DEBUG) -std=c++17 -Wall -pthread
CC=g++-10 
LDFLAGS=-lrt -lptrhead

# wildcard로 서브 디렉토리에서 *.cpp 이름으로 된 파일리스트를 뽑아다
# notdir 함수로 이름만 남긴다.
SRCS=$(notdir $(wildcard $(SRCDIRS)/*.cpp))
OBJS=$(SRCS:.cpp=.o)
# OBJS 파일 이름 앞에다 디렉토리 이름을 붙여준다.
OBJ_OUT=$(patsubst %.o, $(OBJDIRS)/%.o, $(OBJS))
TARGET=$(OBJ_OUT:.o=.out)
DEPS:=$(OBJ_OUT:.o=.d)

all: $(TARGET)
	@echo target $(TARGET)

$(OBJDIRS)/%.o: $(SRCDIRS)/%.cpp
	@echo obj $(OBJDIRS)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -MD -o $@

$(TARGET): $(OBJ_OUT)
	@echo target $(TARGET)
	$(CC) $(CFLAGS) $(OBJ_OUT) $(LDFLAGS) -o $(patsubst %.out, %.o, %.@)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJ_OUT) $(DEPS)

-include $(DEPS)
