#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <vector>

#include "btree.cpp"
using namespace std;

double entropy = 0.0;
char *codebook[size];

class treeNode* genCodeTree(char *str){
	ifstream file(str, ios::in);
	ofstream op("symbollist", ios::out|ios::trunc);
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

void genCodeBookAux(class treeNode *node, char *curr, ofstream *file){
	if(node->getLeft() == NULL && node->getRight() == NULL){
		if(isprint(node->getCh()))
			*file << node->getCh() << "\t\t\t"<< (char)node->getCh() << "\t\t\t" << curr << "\n";
		else
			*file << node->getCh() << "\t\t\t"<< "NA" << "\t\t\t" << curr << "\n";

		codebook[node->getCh()] = new char[strlen(curr)+1];
		strcpy(codebook[node->getCh()], curr);
	}
	else{
		int len = strlen(curr); 
		curr[len] = '0';
		curr[len+1] = '\0';
		genCodeBookAux(node->getLeft(), curr, file);
		curr[len] = '1';
		genCodeBookAux(node->getRight(), curr, file);
		curr[len] = '\0';
	}
}

void genCodeBook(class treeNode *node){
	ofstream file("codebook", ios::out|ios::trunc);
	char curr[size] = "";
	
	file << "NP stands for not printable char\n\n";
	file << "ASCII" << "\t\t" << "Symbol" << "\t\t" << "Huffman Code" <<"\n";

	genCodeBookAux(node, curr, &file);
	file.close();
}

void appendeof(char *str){
	ifstream in(str, ios::in);
	ofstream file("temp", ios::out|ios::trunc);
	
	char ch;
	while(in >> noskipws >> ch){
		file << ch;
	}
	file << '`';
	file.close();
	in.close();
}

void convert_to_huffman(char* inp){
	ofstream file_out("out", ios::out|ios::trunc|ios::binary);
	ifstream file_inp(inp, ios::in);

	vector<bool> out;
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

	int n = out.size();

	while(n % 8 != 0){
		out.push_back(false);
		n++;
	}

	for(i = 0; i < out.size(); i = i + 8){
		k = 0;
		for(j = 0; j < 8;j++){
 			k = k + out[i+j]*pow(2,7 - j);
		}
		c = k;
		// if(c == ' ')
		// 	printf("Space %d\n",i/8);
		cout<<c;
		// file_out << c;
		char str[1];
		str[0] = c; 
		file_out.write(str,sizeof(str));
	}
	file_out.close();
	file_inp.close();
}

int main(int argc, char *argv[]){
	appendeof(argv[1]);

	char str[] = "temp";

	class treeNode *b = genCodeTree(str);
	genCodeBook(b);
	convert_to_huffman(str);
}