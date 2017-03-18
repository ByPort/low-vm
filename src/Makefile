CXX = c++
CXXFLAGS = -std=c++14 -c -Wall
INCLUDES = -I../include

all: memory vm

memory:
	$(CXX) $(CXXFLAGS) $(INCLUDES) memory.cpp

vm:
	$(CXX) $(CXXFLAGS) $(INCLUDES) vm.cpp

clean:
	rm *.o
	find . -type f  ! -name "*.*" ! -name "Makefile" -delete
