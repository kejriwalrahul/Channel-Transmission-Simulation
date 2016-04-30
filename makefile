all:
	g++ -g ./code/main.cpp -o ./bin/main.o -std=c++11
	./bin/main.o ./input/test
	rm ./output/temp
	g++ ./code/makesrc.cpp -o ./bin/src.o
	./bin/src.o ./output/tempbef ./output/srccoded
	rm ./output/tempbef

decode:
	g++ ./code/convtobin.cpp -o ./bin/conv.o 
	./bin/conv.o
	g++ ./code/decode_huffman.cpp -o ./bin/decode.o -std=c++11
	./bin/decode.o ./output/recvdWoutCRC ./output/final_output

debug:
	gdb -q ./bin/main.o

# convert:
# 	python ./code/bintodec.py

# split:
# 	python ./code/split.py ./output/transmitted
# 	python ./code/split.py ./output/tempbef
