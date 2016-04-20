all:
	g++ -g ./code/main.cpp -o ./bin/main.o -std=c++11
	./bin/main.o ./input/test

d:
	gdb -q ./bin/main.o