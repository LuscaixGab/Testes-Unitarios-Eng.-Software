#ifndef arvoreAVL_h
#define arvoreAVL_h

#include "node.h"

//classe "avlTree"
class avlTree{
	public:
		avlTree();
		avlTree(node*);
		bool insert(node&);
		bool remove(node*);
		bool search(int);
		node* searchPointer(int);
		node* leftRot(node*);
		node* rightRot(node*);
		node* rightLeftRot(node*);
		node* leftRightRot(node*);
		node* getRoot();
		node* getMinimum(node*);
		node* getMaximum(node*);
		void transplant(node*, node*);
		void rebalance(node*);
		
	private:
		node* root;
};

#endif
