#ifndef node_h
#define node_h

//bibliotecas
#include <cstdio>
#include <iostream>

using namespace std;

//classe "node"
class node{
	public:
		node(int, node*, node*, node*);
		void setKey(int);
		void setP(node*);
		void setLeft(node*);
		void setRight(node*);
		int getKey();
		node* getP();
		node* getLeft();
		node* getRight();
		int getBalance();
		int getHeight();
		void print();
		
	private:
		int key;
		node* p;
		node* left;
		node* right;
};

#endif