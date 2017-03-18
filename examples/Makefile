CXX = c++
CXXFLAGS = -std=c++14 -Wall
INCLUDES = -I../include
OBJECTS = ../src/*.o

all: general

general:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c general.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) general.o -o general

clean:
	rm *.o
	find . -type f  ! -name "*.*" ! -name "Makefile" -delete
