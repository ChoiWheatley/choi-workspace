# CC = g++-10		# CC := mips-openwrt-linux-gcc
CXX = g++-10	# CXX := mips-openwrt-linux-g++
CFLAGS = -W -Wall
TARGET = Book.out
OBJECTS = Chrono.o Libre.o Libre_main.o 

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

clean :
	rm *.o *.out
