#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
	fstream inp(argv[1],ios::in);
	fstream out(argv[2],ios::out);

	char ch, temp;
	while(inp){
		int i=0;
		ch = 0;
		for(i=0; i<8;i++){

			if(!inp){
				while(i!=8){
					ch*=2;
					i++;
				}
				out << ch;
				out.flush();
				exit(0);
			}

			inp >> temp;
			ch*=2;
			ch+=(temp-48);
		}
		out << ch;
	}

	return 0;
}
