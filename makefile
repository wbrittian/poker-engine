build:
	rm -f ./a.out
	g++ -std=c++17 -g -Wall main.cpp game.cpp player.cpp deck.cpp

run:
	rm -f ./a.out
	g++ -std=c++17 -g -Wall main.cpp game.cpp player.cpp deck.cpp
	./a.out