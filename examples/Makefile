CXX = c++
CXXFLAGS = -std=c++14 -Wall
INCLUDES = -I../include
OBJECTS = ../src/*.o

all: recursive-call mem-mapping

recursive-call:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c recursive-call.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) recursive-call.o -o recursive-call
mem-mapping:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c mem-mapping.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) mem-mapping.o -o mem-mapping

clean:
	rm *.o
	find . -type f  ! -name "*.*" ! -name "Makefile" -delete
