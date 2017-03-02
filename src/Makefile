CXX = c++
CXXFLAGS = -std=c++14 -c
INCLUDES = -I../include

all: memory vm

memory:
	$(CXX) $(CXXFLAGS) $(INCLUDES) memory.cpp

vm:
	$(CXX) $(CXXFLAGS) $(INCLUDES) vm.cpp

clean:
	rm *.o
