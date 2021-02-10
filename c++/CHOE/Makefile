.SUFFIXES: .o .cpp
CXX = g++-10 -std=c++17 -Wall
DEBUG = -g
LIB = libCHOEfltk.a
INC = -I/usr/local/include -I.
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags) $(INC)

# $(wildcard [PATTERN]) 현재 디렉토리에서 패턴과 일치하는 파일리스트

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

#default target
$(LIB): $(OBJS)
	$(AR) rsv $@ $(OBJS)

# $@ 현재 타겟이름
# $< 현재 타겟보다 일찍 변경된 종속항목 리스트 
# $^ 현재 타겟의 종속항목리스트

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# generating dependency files
%.d: %.cpp
	$(CXX) -MM $< > $@

# $(subst from, to, text) text 에서 from 을 찾아 to 로 변경한다.
# $(patsubst pattern, replacement, text) text 에서 pattern을 찾아 replacement로 변경한다.

# include dependency files
-include $(patsubst %.cpp,%.d,$(wildcard *.cpp))

clean:
	$(RM) $(LIB) $(SRCS) *.d 
