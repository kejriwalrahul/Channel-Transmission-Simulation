#include <iostream>
#include <string.h>

using namespace std;
 
char xorc(char a, char b){
	if((a == '1' && b == '1') || (a == '0' && b == '0'))
		return '0';
	else
		return '1';
}

// First bit of generating polynomial, genpoly must be 1.
// Compute CRC takes two strings as input: the first one takes the bitstream 
// whose CRC is to be computed and the other is the generating polynomial bitstring
// of length n. Return value is a string of len n-1 containing the CRC of the first argument,src.

char* computeCRC(char* src, char* genpoly){
	int n = strlen(genpoly) - 1;
	
	char *temp = new char[strlen(src) + n + 1];
	strcpy(temp, src);

	int i,j;
	for(i=0; i < n;i++){
		strcat(temp, "0");
	}

	char *ans = new char[n];

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

	return ans;
}


/*int main(){
	char temp[100]="1101011011";
	char *res = computeCRC(temp, "10011"); 
	cout << res <<endl;
	cout << res[0] << res[3] <<endl;
	cout << computeCRC(strcat(temp,res) , "10011");
	return 0;
}
*/