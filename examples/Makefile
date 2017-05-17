CXX = c++
CXXFLAGS = -std=c++14 -Wall
INCLUDES = -I../include
OBJECTS = ../src/*.o

all: recursive-call mem-mapping

recursive-call: vm
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c recursive-call.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) recursive-call.o -o recursive-call
mem-mapping: vm
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c mem-mapping.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) mem-mapping.o -o mem-mapping

vm:
	$(MAKE) -C ../src

clean:
	find . -type f -name "*.o" -delete
	find . -type f  ! -name "*.*" ! -name "Makefile" -delete
