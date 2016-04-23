#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// using namespace std;
 
char xorc(char a, char b){
	if((a == '1' && b == '1') || (a == '0' && b == '0'))
		return '0';
	else
		return '1';
}

// First bit of generating polynomial, genpoly must be 1.
char* computeCRC(char* src, char* genpoly){
	int n = strlen(genpoly) - 1;
	
	char *temp = malloc(strlen(src) + n + 1);
	// char *temp = new char[strlen(src) + n + 1];
	strcpy(temp, src);

	int i,j;
	for(i=0; i < n;i++){
		strcat(temp, "0");
	}

	char *ans = malloc(n+1);
	// char *ans = new char[n];

	i = 0;
	int bound = strlen(temp)-n; 
	while(i < bound){
		if(temp[i] == '0')
			i++;
		else{
			j = i;
			while(j-i <= n){
				temp[j] = xorc(temp[j], genpoly[j-i]);
				j++;
			}
			i++;
		}
	}

	for(j=0;i<strlen(temp);i++,j++){
		ans[j] = temp[i];
	}

	ans[j] = '\0';
	return ans;
}

/*
int main(){
	cout << computeCRC("1101011011", "10011");
	return 0;
}
*/