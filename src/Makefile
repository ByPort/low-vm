CXX = c++
CXXFLAGS = -std=c++14 -c -Wall
INCLUDES = -I../include

all: vm memory interpreter debugger io

memory:
	$(CXX) $(CXXFLAGS) $(INCLUDES) memory.cpp

vm:
	$(CXX) $(CXXFLAGS) $(INCLUDES) vm.cpp

io:
	$(CXX) $(CXXFLAGS) $(INCLUDES) io.cpp

interpreter:
	$(CXX) $(CXXFLAGS) $(INCLUDES) interpreter.cpp

debugger:
	$(CXX) $(CXXFLAGS) $(INCLUDES) debugger.cpp

clean:
	find . -type f -name "*.o" -delete
	find . -type f  ! -name "*.*" ! -name "Makefile" -delete
