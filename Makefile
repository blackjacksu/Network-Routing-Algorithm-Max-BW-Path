GCC = g++
GCC_OPTIONS = -Wall -g3 -std=c++11 -c

all: main.o graph.o routing.o
	g++ -o Graphs main.o graph.o routing.o

main.o: main.cpp
	$(GCC) $(GCC_OPTIONS) main.cpp

graph.o: graph.cpp
	$(GCC) $(GCC_OPTIONS) graph.cpp
	
routing.o: routing.cpp
	$(GCC) $(GCC_OPTIONS) routing.cpp

clean:
	rm -f *.o *.bin Graphs