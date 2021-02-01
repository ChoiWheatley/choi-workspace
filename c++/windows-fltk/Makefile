CXX = g++
DEBUG = -g
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags) -I. -std=c++17 -Wall
LDFLAGS = $(shell fltk-config --use-gl --use-images --ldflags)
LDSTATIC = $(shell fltk-config --use-gl --use-images --ldstaticflags)
LINK = $(CXX)

TARGET = a.out
OBJS = fl-drawing.o   Axis.o   Function.o   Rectangle.o   Circle.o   Ellipse.o
SRCS = fl-drawing.cpp Axis.cpp Function.cpp Rectangle.cpp Circle.cpp Ellipse.cpp

.SUFFIXES:.o .cxx
%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

all: $(TARGET)
	$(LINK) -o $(TARGET) $(OBJS) $(LDSTATIC)

$(TARGET): $(OBJS)
fl-drawing.o: fl-drawing.cpp
Axis.o: Axis.cpp Axis.h
Function.o: Function.cpp Function.h
Rectangle.o: Rectangle.cpp Rectangle.h
Circle.o: Circle.cpp Circle.h
Ellipse.o: Ellipse.cpp Ellipse.h

clean: 
	rm -f *.o 
	rm -f $(TARGET)
