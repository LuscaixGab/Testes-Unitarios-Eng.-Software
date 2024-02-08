#ifndef arvoreAVL_cpp
#define arvoreAVL_cpp

#include "avlTree.h"
#include "node.cpp"

//construtor sem argumento
avlTree::avlTree(){
	//define a raiz da �rvore como
	// nula (�rvore vazia)
	this->root = NULL;
}

//construtor com argumento
avlTree::avlTree(node* R){
	//aponta o elemento fornecido
	// como sendo a raiz da �rvore
	this->root = R;
}

//busca uma determinada chave dentro da �rvore
bool avlTree::search(int n){
	//ponteiro auxiliar, come�a na raiz da �rvore
	node* x = this->root;
	
	//faz a busca e retorna "true" se encontrar
	// um n� com a chave procurada
	while(x != NULL){
		if(x->getKey() == n)
			return true;
		if(x->getKey() < n)
			x = x->getRight();
		else
			x = x->getLeft();
	}
	
	//se sair do loop significa que n�o
	// encontrou a chave, retorna "false"
	return false;
}

node* avlTree::searchPointer(int n){
	//ponteiro auxiliar, come�a na raiz da �rvore
	node* x = this->root;
	
	//faz a busca e retorna o ponteiro se
	// encontrar um n� com a chave procurada
	while(x != NULL){
		if(x->getKey() == n)
			return x;
		if(x->getKey() < n)
			x = x->getRight();
		else
			x = x->getLeft();
	}
	
	//se sair do loop significa que n�o
	// encontrou o n�, retorna "NULL"
	return NULL;
}

//insere um novo n� na �rvore e faz
// o balanceamento caso seja necess�rio
bool avlTree::insert(node& novo){
	
	//verifica se o elemento j� est� inserido na �rvore
	if(this->search(novo.getKey()))
		return false;
	
	//verifica se a �rvore est� vazia
	if(this->root == NULL){
		novo.setP(NULL);
		novo.setLeft(NULL);
		novo.setRight(NULL);
		this->root = &novo;
		return true;
	}
	
	//inicializa ponteiros auxiliares
	node* x = this->root;
	node* y = NULL;
	
	//encontra o n� que deverer�
	// ser o pai do novo n� 
	while(x != NULL){
		y = x;
		if(x->getKey() < novo.getKey())
			x = x->getRight();
		else
			x = x->getLeft();
	}
	
	//identifica se o n� deve ser inserido
	// � esquerda ou direira de seu pai
	if(y->getKey() < novo.getKey())
		y->setRight(&novo);
	else
		y->setLeft(&novo);
	
	//ajusta os ponteiros do
	// novo n� ap�s a inser��o
	novo.setP(y);
	novo.setLeft(NULL);
	novo.setRight(NULL);
		
	//se o pai do novo n� for a ra�z n�o
	// haver� necessidade de balanceamento
	if(novo.getP()->getP() == NULL)
		return true;
	
	//define um ponteiro para o pai do pai do novo
	// n� para iniciar a an�lise de balanceamento
	node* db = novo.getP()->getP();
	this->rebalance(db);
	
	//finaliza a inser��o
	return true;
}

//verifica se h� n�s desbalanceados e faz as rota��es
// necess�rias para restaurar o equil�biro da �rvore
void avlTree::rebalance(node* x){
	//ponteiros auxiliares
	node* aux = x;
	node* auxP = x->getP();
	
	//come�a no n�vel onde est� "x" e vai descendo at� o n�vel 0
	while(aux != NULL){
		//verifica se est� desbalanceado para a esquerda
		if(aux->getBalance() > 1){
			//verifica se o filho esquerdo est� pendendo para o sentido contr�rio
			if(aux->getLeft()->getBalance() < 0){
				//verifica se o n� desbalanceado � a raiz 
				if(aux == this->root){
					//realiza rota��o esquerda-direita na raiz
					this->root = this->leftRightRot(aux);
					this->root->setP(NULL);
				}
				//n� desbalanceado n�o � a raiz
				else{
					//identifica se o n� desbalanceado � filho direito
					// ou esquerdo e realiza rota��o esquerda-direita
					if(auxP->getRight() == aux){
						auxP->setRight(this->leftRightRot(aux));
						auxP->getRight()->setP(auxP);
					}
					else{
						auxP->setLeft(this->leftRightRot(aux));
						auxP->getLeft()->setP(auxP);
					}
				}
			}
			//filho esquerdo n�o est� pendendo para o sentido contr�rio
			else{
				//verifica se o n� desbalanceado � a raiz
				if(aux == this->root){
					//realiza rota��o direita na raiz
					this->root = this->rightRot(aux);
					this->root->setP(NULL);
				}
				//n� desbalanceado n�o � a raiz
				else{
					//identifica se o n� desbalanceado � filho direito
					// ou esquerdo e realiza a rota��o direita
					if(auxP->getRight() == aux){
						auxP->setRight(this->rightRot(aux));
						auxP->getRight()->setP(auxP);
					}
					else{
						auxP->setLeft(this->rightRot(aux));
						auxP->getLeft()->setP(auxP);
					}
				}
			}
			
		}
		//verifica se est� desbalanceado para a direita
		else if(aux->getBalance() < -1){
			//verifica se o filho direito est� pendendo para o sentido contr�rio
			if(aux->getRight()->getBalance() > 0){
				//verifica se o n� desbalanceado � a raiz
				if(aux == this->root){
					//realiza rota��o direita-esquerda na raiz
					this->root = this->rightLeftRot(aux);
					this->root->setP(NULL);
				}
				//n� desbalanceado n�o � a raiz
				else{
					//identifica se o n� desbalanceado � filho esquerdo
					// ou direito e realiza rota��o direita-esquerda
					if(auxP->getLeft() == aux){
						auxP->setLeft(this->rightLeftRot(aux));
						auxP->getLeft()->setP(auxP);
					}
					else{
						auxP->setRight(this->rightLeftRot(aux));
						auxP->getRight()->setP(auxP);
					}
				}
			}
			//filho direito n�o est� pendendo para o sentido contr�rio
			else{
				//verifica se o n� desbalanceado � a raiz
				if(aux == this->root){
					//realiza rota��o esquerda na raiz
					this->root = this->leftRot(aux);
					this->root->setP(NULL);
				}
				//n� desbalanceado n�o � a raiz
				else{
					//identifica se o n� desbalanceado � filho esquerdo
					// ou direito e realiza rota��o esquerda
					if(auxP->getLeft() == aux){
						auxP->setLeft(this->leftRot(aux));
						auxP->getLeft()->setP(auxP);
					}
					else{
						auxP->setRight(this->leftRot(aux));
						auxP->getRight()->setP(auxP);
					}
				}
			}
		}
		//atualiza os ponteiros
		// (passa para o pr�ximo n�vel)
		aux = auxP;
		if(aux != NULL)
			auxP = aux->getP();
	}
}

//realiza rota��o � direita no n� informado
node* avlTree::rightRot(node* x){
	//ponteiros auxiliares	
	node* y = x->getLeft();
	node* b = y->getRight();
	
	//coloca a sub�rvore enraizada por b
	// como a nova sub�rvore esquerda de x
	x->setLeft(b);
	
	//define a nova sub�rvore enraizada por x
	// como sendo a sub�rvore direita de y
	y->setRight(x);
	x->setP(y);
	
	//ajusta o pai de b
	if(b != NULL)
		b->setP(y->getRight());
	
	//retorna y
	return y;
}

//realiza rota��o � esquerda no n� informado
node* avlTree::leftRot(node* x){
	//ponteiros auxiliares
	node* y = x->getRight();
	node* b = y->getLeft();
	
	//define a sub�rvore enraizada por b como
	// sendo a nova sub�rvore direita de x
	x->setRight(b);
	
	//coloca a nova sub�rvore enraizada por
	// x como sub�rvore esquerda de y
	y->setLeft(x);
	x->setP(y);
	
	//ajusta o pai de b
	if(b != NULL)
		b->setP(y->getLeft());
	
	//retorna y
	return y;
}

//realiza rota��o esquerda-direita no n� informado
node* avlTree::leftRightRot(node* z){	
	//faz rota��o � esquerda no filho esquerdo de z
	node* x = z->getLeft();
	node* y = this->leftRot(x);
	z->setLeft(y);
	y->setP(z);
	
	//faz rota��o � direita em z
	node* w = this->rightRot(z);
	
	//retorna w
	return w;
}

//realiza rota��o direita-esquerda no n� informado
node* avlTree::rightLeftRot(node* z){
	//faz rota��o � direita no filho direito de z
	node* x = z->getRight();
	node* y = this->rightRot(x);
	z->setRight(y);
	y->setP(z);
	
	//faz rota��o � esquerda em z
	node* w = this->leftRot(z);
	
	//retorna w
	return w;
}

//remove um n� da �rvore e verifica se realiza as devidas rota��es
// (caso sejam necess�rias) para manter o balanceamento
bool avlTree::remove(node* z){	
	//se o n� for nulo ou se ele n�o pertencer � �rvore n�o far� nada
	if((z == NULL) or (!this->search(z->getKey())))
		return false;
	
	//ponteiro auxiliar para o pai de z
	node* db = z->getP();
	
	//se o n� n�o possuir filho � esquerda
	if(z->getLeft() == NULL)
		this->transplant(z, z->getRight()); //substitui pela sub�rvore direita
	//se o n� n�o possuir filho � direita 
	else if(z->getRight() == NULL)
		this->transplant(z, z->getLeft()); //substitui pela sub�rvore esquerda
	//o n� a ser removido possui os dois filhos
	else{
		//encontra o menor elemento da sub�rvore direita do n� a ser removido
		node* y = this->getMinimum(z->getRight());
		db = y->getP();
		
		//verifica se o menor elemento n�o est� diretamente
		// � direita do elemento a ser removido
		if(y != z->getRight()){
			//transplanta a sub�rvore � direita do menor elemento no lugar dele
			this->transplant(y, y->getRight());
			//transfere a sub�rvore direita do n� a ser removido para y
			y->setRight(z->getRight());
			y->getRight()->setP(y);
			z->setRight(NULL);
		}
		//coloca a sub�rvore enraizada por y no lugar do n� a ser removido
		this->transplant(z, y);
		//transfere a sub�rvore esquerda do n� removido para y
		y->setLeft(z->getLeft());
		y->getLeft()->setP(y);
		z->setLeft(NULL);
		z->setRight(NULL);
	}
	
	//verifica o balanceamento da �rvore ap�s a remo��o
	if(db != NULL)
		this->rebalance(db);
	
	//finaliza a remo��o
	return true;
}

//retorna um ponteiro para o n� que � raiz da �rvore
node* avlTree::getRoot(){
	return this->root;
}

//retorna um ponteiro para o menor valor
// da �rvore enraizada pelo n� informado
node* avlTree::getMinimum(node* x){
	if (x == NULL)
		return NULL;

	//ponteiro auxiliar
	node* min = x;
	
	//encontra e retorna um ponteiro
	// para o n� mais a esquerda
	while(min->getLeft() != NULL)
		min = min->getLeft();
	
	return min;
}

//retorna um ponteiro para o maior valor
// da �rvore enraizada pelo n� informado
node* avlTree::getMaximum(node* x){
	if (x == NULL)
		return NULL;

	//ponteiro auxiliar
	node* max = x;
	
	//encontra e retorna um ponteiro
	// para o n� mais a direita
	while(max->getRight() != NULL)
		max = max->getRight();
	return max;
}

//coloca a sub�rvore enraizada por "v" no lugar
// lugar da sub�rvore enraizada por "u"
void avlTree::transplant(node* u, node* v){
	//verifica se "u" � raiz
	if(u->getP() == NULL)
		this->root = v;
	//se "u" n�o for raiz
	else
		//identifica se "u" � filho esquerdo ou direito e define
		// "v" como novo filho do n� que era pai de "u"
		if(u == u->getP()->getLeft())
			u->getP()->setLeft(v);
		else
			u->getP()->setRight(v);
	
	//define o novo pai de "v"
	if(v != NULL)
		v->setP(u->getP());
	
	//remove o pai de "u"
	u->setP(NULL);
}

#endif
