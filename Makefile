make: snake.cpp
	g++ snake.cpp -o snake -lncurses

clean:
	rm -rf snake