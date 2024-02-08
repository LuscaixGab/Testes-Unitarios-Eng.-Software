#ifndef node_cpp
#define node_cpp

#include "node.h"

//construtor único
node::node(int KEY, node* P, node* LEFT, node* RIGHT){
	//define a chave, o pai e os filhos
	this->setKey(KEY);
	this->setP(P);
	this->setLeft(LEFT);
	this->setRight(RIGHT);
}

//altera a chave do nó
void node::setKey(int chave){
	this->key = chave;
}

//altera o pai do nó
void node::setP(node* P){
	this->p = P;
}

//altera o filho esquerdo do nó
void node::setLeft(node* L){
	this->left = L;
}

//altera o filho direito do nó
void node::setRight(node* R){
	this->right = R;
}

//retorna a chave contida no nó
int node::getKey(){
	return this->key;
}

//retorna um ponteiro para o pai do nó
node* node::getP(){
	return this->p;
}

//retorna um ponteiro para o filho esquerdo do nó
node* node::getLeft(){
	return this->left;
}

//retorna um ponteiro para o filho direito do nó
node* node::getRight(){
	return this->right;
}

//calcula e retorna a altura do nó
int node::getHeight(){
	//verifica se é um nó folha, cuja altura é zero
	if((this->getLeft() == NULL) and (this->getRight() == NULL))
		return 0;
	
	//variáveis para armazenar o tamanho das subárvores do nó
	int leftHeight = 0, rightHeight = 0;
	
	//verifica quais filhos o nó tem e chama a função de forma
	// recursiva para calcular a altura deles
	if(this->getLeft() != NULL)
		leftHeight = this->getLeft()->getHeight();
	if(this->getRight() != NULL)
		rightHeight = this->getRight()->getHeight();
	
	//verifica qual dos filhos possui a maior a altura
	// e retorna a maior altura + 1 (a altura do nó atual)
	if(leftHeight > rightHeight)
		return leftHeight + 1;
	return rightHeight + 1;
}

int node::getBalance(){
	//variáveis para armazenar a
	// altura dos filhos do nó
	int esq = -1, dir = -1;
	
	//verifica quais filhos o nó tem
	// e calcula a altura de cada um deles
	if(this->getLeft() != NULL)
		esq = this->getLeft()->getHeight();
	if(this->getRight() != NULL)
		dir = this->getRight()->getHeight();
	
	//retorna a diferença entre a altura
	// do filho esquerdo e do filho direito
	return esq - dir;
}

//imprime as informações do nó
void node::print(){
	//imprime a chave do nó
	cout << "Node KEY: " << this->getKey() << endl;
	
	//imprime a chave do nó pai
	cout << "Father: ";
	if(this->getP() != NULL)
		cout << this->getP()->getKey() << endl;
	else
		cout << "---" << endl;
	
	//imprime a chave do filho esquerdo
	cout << "Left Child: ";
	if(this->getLeft() != NULL)
		cout << this->getLeft()->getKey() << endl;
	else
		cout << "---" << endl;
	
	//imprime a chave do filho direito
	cout << "Right Child: ";
	if(this->getRight() != NULL)
		cout << this->getRight()->getKey() << endl;
	else
		cout << "---" << endl;
}

#endif
