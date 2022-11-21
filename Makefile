GCC = g++
GCC_OPTIONS = -g3 -std=c++11 -c

all: main.o graph.o
	g++ -o Graphs main.o graph.o

graph.o: graph.cpp
	$(GCC) $(GCC_OPTIONS) graph.cpp
	
main.o: main.cpp
	$(GCC) $(GCC_OPTIONS) main.cpp

clean:
	rm -f *.o *.bin Graphs