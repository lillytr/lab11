CXX = g++

CXXFLAGS = -Wall -std=c++17
TARGETS = prog1 

all: $(TARGETS)
prog1: main.o
	$(CXX) $(CXXFLAGS) main.o -o prog1



main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp


run1: prog1 
	./prog1
clean: 
	rm -f *.o $(TARGETS)