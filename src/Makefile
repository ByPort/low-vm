CXX = c++
CXXFLAGS = -std=c++14 -c -Wall
INCLUDES = -I../include

all: util memory vm

memory:
	$(CXX) $(CXXFLAGS) $(INCLUDES) memory.cpp

vm:
	$(CXX) $(CXXFLAGS) $(INCLUDES) vm.cpp

util: vector

vector:
	$(CXX) $(CXXFLAGS) $(INCLUDES) util/vector.cpp

clean:
	find . -type f -name "*.o" -delete
	find . -type f ! -name "*.*" ! -name "Makefile" -delete
