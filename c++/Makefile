CXX = g++ -std=c++17
DEBUG = -g
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags) -I. -std=c++17 -Wall
LDFLAGS = $(shell fltk-config --use-gl --use-images --ldflags)
LDSTATIC = $(shell fltk-config --use-gl --use-images --ldstaticflags)
LINK = $(CXX)

TARGET = a.out
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

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

# generating dependency files
%.d: %.cpp
	$(CXX) -MM $< > $@

# include dependency files
-include $(patsubst %.cpp,%.d,$(wildcard *.cpp))

clean: 
	rm -f *.o *.d
	rm -f $(TARGET)
