#ifndef node_cpp
#define node_cpp

#include "node.h"

//construtor �nico
node::node(int KEY, node* P, node* LEFT, node* RIGHT){
	//define a chave, o pai e os filhos
	this->setKey(KEY);
	this->setP(P);
	this->setLeft(LEFT);
	this->setRight(RIGHT);
}

//altera a chave do n�
void node::setKey(int chave){
	this->key = chave;
}

//altera o pai do n�
void node::setP(node* P){
	this->p = P;
}

//altera o filho esquerdo do n�
void node::setLeft(node* L){
	this->left = L;
}

//altera o filho direito do n�
void node::setRight(node* R){
	this->right = R;
}

//retorna a chave contida no n�
int node::getKey(){
	return this->key;
}

//retorna um ponteiro para o pai do n�
node* node::getP(){
	return this->p;
}

//retorna um ponteiro para o filho esquerdo do n�
node* node::getLeft(){
	return this->left;
}

//retorna um ponteiro para o filho direito do n�
node* node::getRight(){
	return this->right;
}

//calcula e retorna a altura do n�
int node::getHeight(){
	//verifica se � um n� folha, cuja altura � zero
	if((this->getLeft() == NULL) and (this->getRight() == NULL))
		return 0;
	
	//vari�veis para armazenar o tamanho das sub�rvores do n�
	int leftHeight = 0, rightHeight = 0;
	
	//verifica quais filhos o n� tem e chama a fun��o de forma
	// recursiva para calcular a altura deles
	if(this->getLeft() != NULL)
		leftHeight = this->getLeft()->getHeight();
	if(this->getRight() != NULL)
		rightHeight = this->getRight()->getHeight();
	
	//verifica qual dos filhos possui a maior a altura
	// e retorna a maior altura + 1 (a altura do n� atual)
	if(leftHeight > rightHeight)
		return leftHeight + 1;
	return rightHeight + 1;
}

int node::getBalance(){
	//vari�veis para armazenar a
	// altura dos filhos do n�
	int esq = -1, dir = -1;
	
	//verifica quais filhos o n� tem
	// e calcula a altura de cada um deles
	if(this->getLeft() != NULL)
		esq = this->getLeft()->getHeight();
	if(this->getRight() != NULL)
		dir = this->getRight()->getHeight();
	
	//retorna a diferen�a entre a altura
	// do filho esquerdo e do filho direito
	return esq - dir;
}

//imprime as informa��es do n�
void node::print(){
	//imprime a chave do n�
	cout << "Node KEY: " << this->getKey() << endl;
	
	//imprime a chave do n� pai
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
