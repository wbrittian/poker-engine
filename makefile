build:
	rm -f ./a.out
	g++ -std=c++17 -Wall src/*.cpp

run:
	./a.out