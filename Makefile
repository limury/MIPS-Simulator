CXX	= g++
CXXFLAGS= -Wall -g
BUILD	= main
PHONY 	= clean

build: $(BUILD)

main: main.o
		$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(BUILD)
