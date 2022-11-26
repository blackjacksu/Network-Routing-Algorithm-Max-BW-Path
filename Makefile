GCC = g++
GCC_OPTIONS = -Wall -g3 -std=c++11 -c

all: main.o graph.o routing.o datastruct.o
	g++ -o Graphs main.o graph.o routing.o datastruct.o

main.o: main.cpp
	$(GCC) $(GCC_OPTIONS) main.cpp

graph.o: graph.cpp graph.h
	$(GCC) $(GCC_OPTIONS) graph.cpp
	
routing.o: routing.cpp routing.h
	$(GCC) $(GCC_OPTIONS) routing.cpp

datastruct.o: datastruct.cpp datastruct.h
	$(GCC) $(GCC_OPTIONS) datastruct.cpp

clean:
	rm -f *.o *.bin Graphs