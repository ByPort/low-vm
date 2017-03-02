CXX = c++
CXXFLAGS = -std=c++14
INCLUDES = -I../include
OBJECTS = ../src/*.o general.o

general:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c general.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o general

clean:
	rm *.o
