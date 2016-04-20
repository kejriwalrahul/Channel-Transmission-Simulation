#include <iostream>
#include <stdio.h>

const int size = 256;

class treeNode{
	char ch;
	int freq;
	class treeNode *left, *right;

public:

 	treeNode(){
		left = NULL; 
		right = NULL;
		freq = 0;
		ch = 0;		
	}

	treeNode(char val){
		left = right = NULL;
		ch = val;
		freq = 0;
	}

	void incf(){
		freq += 1;
	}

	void decf(){
		freq -= 1;
	}

	void setfreq(int freq){
		this->freq = freq;
	}
	
	int getCh(){
		return ch;
	}

	int getfreq(){
		return freq;
	}
		
	void setLeft(class treeNode *left){
		this-> left = left;
	}

	void setRight(class treeNode *right){
		this-> right = right;
	}	

	class treeNode* getLeft(){
		return this->left;
	}

	class treeNode* getRight(){
		return this->right;
	}

	void print(){
		if(this->left == NULL && this->right == NULL){
			printf("%d,",this->ch);
		}
		else{
			if(this->left != NULL)
				this->left->print();
			if(this->right != NULL)
				this->right->print();
		}
	}
};

class heap{
	class treeNode *node[size];
	int hsize;

public:
	heap(){
		int i;
		for(i=0; i < size; i++)
			node[i] = NULL;
		hsize = 0;
	}

	int left(int i){
		return 2*i + 1;
	}

	int right(int i){
		return 2*i + 2;
	}

	int parent(int i){
		if(i % 2 == 0)
			return i/2 -1;
		else
			return i/2;
	}

	int getSize(){
		return hsize;
	}

	void swap(int i,int j){
		class treeNode *temp = node[i];
		node[i] = node[j];
		node[j] = temp;
	}

	void heapify(int i){
		if(i >= hsize)
			return;

		int min = node[i]->getfreq();
		int mini = i;

		if(left(i) < hsize && node[left(i)]->getfreq() < min){
			min = node[left(i)]->getfreq();
			mini = left(i);
		}

		if(right(i) < hsize && node[right(i)]->getfreq() < min){
			min = node[right(i)]->getfreq();
			mini = right(i);
		}

		if(mini == i)
			return;

		swap(i, mini);
		heapify(mini);
	}

	void push(class treeNode *c){
		if(hsize >= size)
			return;

		node[hsize] = c;
		hsize += 1;

		int curr = hsize-1;
		int p = parent(curr);
		while(p>=0 && node[p]->getfreq() > node[curr]->getfreq()){
			swap(p, curr);
			curr = p;
			p = parent(curr);
		}
	}

	class treeNode* pop(){
		if(hsize == 0)
			return NULL;

		class treeNode *temp = node[0];

		node[0] = node[hsize-1];
		node[hsize-1] = NULL;
		hsize -= 1;
		heapify(0);

		return temp;
	}

	void print(){
		int i;
		for(i=0;i < hsize;i++)
			printf("(%d , %d) ",node[i]->getCh(), node[i]->getfreq());
	}
};
