#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{
	unordered_map<string,int> decode;
	FILE *fp = fopen("./output/mrcodebook","r");
	FILE *fout = fopen("./output/final_output","w");
	FILE *fi = fopen("./output/transmitted","r");
	
	cout<<"here";
	int i,c,n;
	char h[256][256], s[256], j,te[2];
	for(i=0;i<256;i++){
		h[i][0] = '\0';
	}
	i=0;
	while(fscanf(fp,"%d",&i)>0){
		j = fgetc(fp);
		fgets(s,256,fp);
		strcat(h[i],s);
		n = strlen(h[i]);
		h[i][n-1] = '\0';
	}
	for(i=0;i<256;i++){
		pair<string,int> temp (h[i],i);
		decode.insert(temp);
	}
	s[0] = '\0';
	while((te[0]=getc(fi))!=EOF){
		te[1]='\0';
		strcat(s,te);
		unordered_map<string,int>::const_iterator has = decode.find(s);
		if (has != decode.end())
		{
			if(has->second != '`'){
				fprintf(fout, "%c", has->second);
				s[0] = '\0';
			}
			else{
				break;
			}
		}
	
	}
	return 0;
}