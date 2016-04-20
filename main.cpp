#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <unordered_map>
#include <string.h>

#include "btree.cpp"

using namespace std;
double entropy = 0.0;

unordered_map<char, char*> codebook;

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

		codebook.emplace((char)node->getCh(),curr)
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

int main(int argc, char *argv[]){
	class treeNode *b = genCodeTree(argv[1]);
	genCodeBook(b);
}