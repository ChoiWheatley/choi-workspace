.SUFFIXES: .o .cpp
CXX = g++-10
DEBUG = -g
LIB = libPPPfltk.a
INC = -I/usr/local/include -I.
DEP = Makefile.d
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags) $(INC) -std=c++17 -Wall

SRCS = Simple_window.cpp GUI.cpp Graph.cpp Window.cpp
OBJS = $(SRCS:.cpp=.o)

# default target
# AR: Archieve utility (ar rs libc.a test.o)
$(LIB): $(OBJS) 
	$(MAKE) dep
	$(AR) rsv $@ $(OBJS)

# Generating dependency files
dep: 
	$(CXX) -MM $(SRCS) > $(DEP)

# $@: 현재 타겟의 이름, 
# $<: 현재 타겟보다 일찍 변경된 종속항목 리스트
# $^: 현재 타겟의 종속항목리스트

# %.o: %.cpp 의 경우 모든 .cpp 파일을 .o 파일로 compile 하겠다.
%.o:  %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $< -o $@

%.d: %.cpp
	$(CXX) -MM $< > $(DEP)

# $(wildcard [PATTERN]): 현재 디렉토리에서 패턴과 일치하는 파일리스트
# include dependency files to have g++ recompile necessary sources
ifeq ($(DEP), $(wildcard $(DEP)))
	-include %.d
endif

clean:
	rm -f *.o *.d $(LIB)
