#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <vector>

#include "btree.cpp"
#include "crc.cpp"

using namespace std;

double entropy = 0.0;
char *codebook[size];
vector<bool> out;

class treeNode* genCodeTree(char *str){
	ifstream file(str, ios::in);
	ofstream op("./output/symbollist", ios::out|ios::trunc);
	char ch;
	class treeNode *freq[size];
	int total = 0;

	int i;
	for(i=0; i < size; i++){
		freq[i] = new class treeNode(i);
	}

	while(file){
		total++;
		file >> noskipws >>ch;
		freq[ch]->incf();
	}
	freq[ch]->decf();
	total--;
	file.close();

	class heap h;
	op << "NP stands for not printable char\n\n";
	op << "ASCII" << "\t\t" << "Symbol" << "\t\t" << "Count" << "\t\t" << "Probability" <<"\n";
	// op << ;
	for(i=0; i<size; i++){
		if(freq[i]->getfreq() != 0){
			h.push(freq[i]);

			double f = (double)freq[i]->getfreq();
			if(isprint(i))
				op << i << "\t\t\t" << char(i) << "\t\t\t" << freq[i]->getfreq() << "\t\t\t" << fixed << setprecision(8) << f/total <<"\n";
			else
				op << i << "\t\t\t" << "NP" << "\t\t\t" << freq[i]->getfreq() << "\t\t\t" << fixed << setprecision(8) << f/total <<"\n";
			entropy += (f/total)*log2(((double)total)/f);
		}
	}
	op << "\nEntropy = " << entropy;
	op.close();

	class treeNode *a, *b;
	while(h.getSize() != 1){
		if(h.getSize() == 1)
			break;
		a = h.pop();
		b = h.pop();

		class treeNode *temp = new class treeNode('`');
		temp->setfreq(a->getfreq() + b->getfreq());
		temp->setLeft(b);
		temp->setRight(a);
		h.push(temp);
	}
	a = h.pop();
	return a;	
}

void genCodeBookAux(class treeNode *node, char *curr, ofstream *file,ofstream *file2 ){
	if(node->getLeft() == NULL && node->getRight() == NULL){
		if(isprint(node->getCh()))
			*file << node->getCh() << "\t\t\t"<< (char)node->getCh() << "\t\t\t" << curr << "\n";
		else
			*file << node->getCh() << "\t\t\t"<< "NA" << "\t\t\t" << curr << "\n";

		*file2 << node->getCh() << "\n" << curr << "\n";
		codebook[node->getCh()] = new char[strlen(curr)+1];
		strcpy(codebook[node->getCh()], curr);
	}
	else{
		int len = strlen(curr); 
		curr[len] = '0';
		curr[len+1] = '\0';
		genCodeBookAux(node->getLeft(), curr, file,file2);
		curr[len] = '1';
		genCodeBookAux(node->getRight(), curr, file,file2);
		curr[len] = '\0';
	}
}

void genCodeBook(class treeNode *node){
	ofstream file("./output/codebook", ios::out|ios::trunc);
	ofstream file2("./output/mrcodebook", ios::out|ios::trunc);
	char curr[size] = "";
	
	file << "NP stands for not printable char\n\n";
	file << "ASCII" << "\t\t" << "Symbol" << "\t\t" << "Huffman Code" <<"\n";

	genCodeBookAux(node, curr, &file, &file2);
	file.close();
	file2.close();
}

void appendeof(char *str, char *str2){
	ifstream in(str, ios::in);
	ofstream file(str2, ios::out|ios::trunc);
	
	char ch;
	while(in >> noskipws >> ch){
		file << ch;
	}
	file << '`';
	file.close();
	in.close();
}

void convert_to_huffman(char* inp){
	ifstream file_inp(inp, ios::in);

	char c;
	int i,j,k;
	
	while(file_inp >> noskipws >> c){
		for(i = 0 ; i < strlen(codebook[c]) ; i++){
			if(codebook[c][i] == '1')
				out.push_back(true);
			else
				out.push_back(false);
		}
	}
	file_inp.close();

	int n = out.size();
	while(n % 5 != 0){
		out.push_back(false);
		n++;
	}

	FILE *fp = fopen("./output/tempbef","w");
	for(i=0; i < out.size();i++)
		fprintf(fp,"%d",(out[i]==true)?1:0);
	fclose(fp);

	// add redundancy bits
	vector<bool> temp;
	n = out.size();
	char src[6], *res;
	for(i=0; i < n; i+=5){
		src[5] = '\0';
		for(j=0; j < 5; j++){
			temp.push_back(out[i+j]);
			src[j] = (out[i+j] == true)?'1':'0';
		}
		res = computeCRC(src,"1011");
		temp.push_back(((res[0]=='1')?true:false));
		temp.push_back(((res[1]=='1')?true:false));
		temp.push_back(((res[2]=='1')?true:false));
	}
	out = temp;

	ofstream file_out("./output/out", ios::out|ios::trunc|ios::binary);
	// write encoded stream to file
	for(i = 0; i < out.size(); i = i + 8){
		
		k = 0;
		for(j = 0; j < 8;j++){
 			k = k + out[i+j]*pow(2,7 - j);
		}

		char str[1];
		str[0] = k; 
		file_out.write(str,sizeof(str));
	}
	file_out.close();
}

int main(int argc, char *argv[]){
	char str[] = "./output/temp";

	appendeof(argv[1], str);
	class treeNode *b = genCodeTree(str);
	genCodeBook(b);
	convert_to_huffman(str);
}