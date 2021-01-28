CXX = g++
DEBUG = -g
CXXFLAGS = $(shell fltk-config --cxxflags) -I. -std=c++17 -Wall
LDFLAGS = $(shell fltk-config --ldflags)
LDSTATIC = $(shell fltk-config --ldstaticflags)
LINK = $(CXX)

TARGET = a.out
OBJS = fl-drawing.o   Axis.o   Function.o
SRCS = fl-drawing.cpp Axis.cpp Function.cpp

.SUFFIXES:.o .cxx
%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)

$(TARGET): $(OBJS)
fl-drawing.o: fl-drawing.cpp
Axis.o: Axis.cpp Axis.h
Function.o: Function.cpp Function.h

clean: 
	rm -f *.o 
	rm -f $(TARGET)
