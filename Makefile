CXX	= g++
CXXFLAGS=  -g
BUILD	= main
PHONY 	= clean

build: $(BUILD)

main: main.o
		$(CXX) $(CXXFLAGS) -o main main.o

main.o: main.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c main.cpp

Memory.o: Memory.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c Memory.cpp

clean:
	rm -f *.o $(BUILD)

