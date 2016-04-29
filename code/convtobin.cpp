#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

char* conv(int c){
  char *str = new char[9];
  int i;
  for(i = 0;i<8;i++){
    str[7-i] = (c%2)?'1':'0';
    c /= 2;
  }
  str[8] = '\0';
  return str;
}

int main(){
	fstream fin("./output/tempoutr",ios::in);
	fstream fout("./output/transmitted",ios::out);

	int temp;
	while(fin){
		fin >> temp;
		char *tmp = conv(temp);
		fout << tmp[0] << tmp[1] << tmp[2] << tmp[3] << tmp[4];
	}
	return 0;
}