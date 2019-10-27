CXX	= g++
CXXFLAGS=  -g -Wall
BUILD	= main
PHONY 	= clean

build: $(BUILD)

main: main.o Memory.o RType.o JType.o IType.o
		$(CXX) $(CXXFLAGS) -o main main.o Memory.o RType.o JType.o IType.o

main.o: main.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c main.cpp

Memory.o: Memory.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c Memory.cpp

RType.o: RType.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c RType.cpp

JType.o: JType.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c JType.cpp

IType.o: IType.cpp Memory.h includes.h
		$(CXX) $(CXXFLAGS) -c IType.cpp

clean:
	rm -f *.o $(BUILD)

