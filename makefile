all:
	g++ -g main.cpp -o main.o -std=c++11
	./main.o test

d:
	gdb -q main.o