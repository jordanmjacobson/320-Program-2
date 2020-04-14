FLAGS = -Wall -Wextra -DDebug -g -std=c++14

all: cache-sim

Line.o: Line.cpp
	g++ $(FLAGS) -c Line.cpp -o Line.o

cache-sim: cache-sim.o Line.o
	g++ $(FLAGS) cache-sim.o Line.o -o cache-sim

cache-sim.o: cache-sim.cpp
	g++ $(FLAGS) -c cache-sim.cpp -o cache-sim.o

clean:
	rm *.o
	rm -rf cache-sim output.txt
