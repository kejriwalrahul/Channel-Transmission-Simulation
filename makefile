all:
	g++ -g ./code/main.cpp -o ./bin/main.o -std=c++11
	./bin/main.o ./input/test

decode:
	g++ ./code/decode_huffman.cpp -o ./bin/decode.o -std=c++11
	./bin/decode.o

d:
	gdb -q ./bin/main.o