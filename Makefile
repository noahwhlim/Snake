make: main.cpp board.hpp
	g++ main.cpp -o main -lncurses

clean:
	rm -rf snake