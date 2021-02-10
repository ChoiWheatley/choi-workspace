.SUFFIXES: .o .cpp
CXX = g++-10 -std=c++17
DEBUG = -g
INC = -I/usr/local/include -I./CHOE -I.
LINK = $(CXX) -L$(DIRS) $(LIBS) $(LDFLAGS) $(LDSTATIC) 
LIBS = -lCHOEfltk
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags) $(INC)
LDFLAGS = $(shell fltk-config --use-gl --use-images --ldflags) 
LDSTATIC = $(shell fltk-config --use-gl --use-images --ldstaticflags)
DIRS = CHOE 

SRCS = sample.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = a.out

all: $(LIBS) $(TARGET)

# default target
$(TARGET): $(OBJS)
	$(LINK) -o $@ $(OBJS) 

$(LIBS): 
	@for d in $(DIRS); \
		do \
				$(MAKE) -C $$d; \
		done


# $<: 현재 타겟보다 일찍 변경된 종속항목 리스트
# %.o: %.cpp 의 경우 모든 .cpp 파일을 .o 파일로 compile 하겠다는 의미
%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

clean: 
	$(RM) $(TARGET) *.o  
	@for d in $(DIRS); \
	do \
			$(MAKE) -C $$d clean; \
	done
