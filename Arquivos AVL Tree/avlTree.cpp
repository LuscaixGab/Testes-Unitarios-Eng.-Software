#ifndef arvoreAVL_cpp
#define arvoreAVL_cpp

#include "avlTree.h"
#include "node.cpp"

//construtor sem argumento
avlTree::avlTree(){
	//define a raiz da árvore como
	// nula (árvore vazia)
	this->root = NULL;
}

//construtor com argumento
avlTree::avlTree(node* R){
	//aponta o elemento fornecido
	// como sendo a raiz da árvore
	this->root = R;
}

//busca uma determinada chave dentro da árvore
bool avlTree::search(int n){
	//ponteiro auxiliar, começa na raiz da árvore
	node* x = this->root;
	
	//faz a busca e retorna "true" se encontrar
	// um nó com a chave procurada
	while(x != NULL){
		if(x->getKey() == n)
			return true;
		if(x->getKey() < n)
			x = x->getRight();
		else
			x = x->getLeft();
	}
	
	//se sair do loop significa que não
	// encontrou a chave, retorna "false"
	return false;
}

node* avlTree::searchPointer(int n){
	//ponteiro auxiliar, começa na raiz da árvore
	node* x = this->root;
	
	//faz a busca e retorna o ponteiro se
	// encontrar um nó com a chave procurada
	while(x != NULL){
		if(x->getKey() == n)
			return x;
		if(x->getKey() < n)
			x = x->getRight();
		else
			x = x->getLeft();
	}
	
	//se sair do loop significa que não
	// encontrou o nó, retorna "NULL"
	return NULL;
}

//insere um novo nó na árvore e faz
// o balanceamento caso seja necessário
bool avlTree::insert(node& novo){
	
	//verifica se o elemento já está inserido na árvore
	if(this->search(novo.getKey()))
		return false;
	
	//verifica se a árvore está vazia
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
	
	//encontra o nó que devererá
	// ser o pai do novo nó 
	while(x != NULL){
		y = x;
		if(x->getKey() < novo.getKey())
			x = x->getRight();
		else
			x = x->getLeft();
	}
	
	//identifica se o nó deve ser inserido
	// à esquerda ou direira de seu pai
	if(y->getKey() < novo.getKey())
		y->setRight(&novo);
	else
		y->setLeft(&novo);
	
	//ajusta os ponteiros do
	// novo nó após a inserção
	novo.setP(y);
	novo.setLeft(NULL);
	novo.setRight(NULL);
		
	//se o pai do novo nó for a raíz não
	// haverá necessidade de balanceamento
	if(novo.getP()->getP() == NULL)
		return true;
	
	//define um ponteiro para o pai do pai do novo
	// nó para iniciar a análise de balanceamento
	node* db = novo.getP()->getP();
	this->rebalance(db);
	
	//finaliza a inserção
	return true;
}

//verifica se há nós desbalanceados e faz as rotações
// necessárias para restaurar o equilíbiro da árvore
void avlTree::rebalance(node* x){
	//ponteiros auxiliares
	node* aux = x;
	node* auxP = x->getP();
	
	//começa no nível onde está "x" e vai descendo até o nível 0
	while(aux != NULL){
		//verifica se está desbalanceado para a esquerda
		if(aux->getBalance() > 1){
			//verifica se o filho esquerdo está pendendo para o sentido contrário
			if(aux->getLeft()->getBalance() < 0){
				//verifica se o nó desbalanceado é a raiz 
				if(aux == this->root){
					//realiza rotação esquerda-direita na raiz
					this->root = this->leftRightRot(aux);
					this->root->setP(NULL);
				}
				//nó desbalanceado não é a raiz
				else{
					//identifica se o nó desbalanceado é filho direito
					// ou esquerdo e realiza rotação esquerda-direita
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
			//filho esquerdo não está pendendo para o sentido contrário
			else{
				//verifica se o nó desbalanceado é a raiz
				if(aux == this->root){
					//realiza rotação direita na raiz
					this->root = this->rightRot(aux);
					this->root->setP(NULL);
				}
				//nó desbalanceado não é a raiz
				else{
					//identifica se o nó desbalanceado é filho direito
					// ou esquerdo e realiza a rotação direita
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
		//verifica se está desbalanceado para a direita
		else if(aux->getBalance() < -1){
			//verifica se o filho direito está pendendo para o sentido contrário
			if(aux->getRight()->getBalance() > 0){
				//verifica se o nó desbalanceado é a raiz
				if(aux == this->root){
					//realiza rotação direita-esquerda na raiz
					this->root = this->rightLeftRot(aux);
					this->root->setP(NULL);
				}
				//nó desbalanceado não é a raiz
				else{
					//identifica se o nó desbalanceado é filho esquerdo
					// ou direito e realiza rotação direita-esquerda
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
			//filho direito não está pendendo para o sentido contrário
			else{
				//verifica se o nó desbalanceado é a raiz
				if(aux == this->root){
					//realiza rotação esquerda na raiz
					this->root = this->leftRot(aux);
					this->root->setP(NULL);
				}
				//nó desbalanceado não é a raiz
				else{
					//identifica se o nó desbalanceado é filho esquerdo
					// ou direito e realiza rotação esquerda
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
		// (passa para o próximo nível)
		aux = auxP;
		if(aux != NULL)
			auxP = aux->getP();
	}
}

//realiza rotação à direita no nó informado
node* avlTree::rightRot(node* x){
	//ponteiros auxiliares	
	node* y = x->getLeft();
	node* b = y->getRight();
	
	//coloca a subárvore enraizada por b
	// como a nova subárvore esquerda de x
	x->setLeft(b);
	
	//define a nova subárvore enraizada por x
	// como sendo a subárvore direita de y
	y->setRight(x);
	x->setP(y);
	
	//ajusta o pai de b
	if(b != NULL)
		b->setP(y->getRight());
	
	//retorna y
	return y;
}

//realiza rotação à esquerda no nó informado
node* avlTree::leftRot(node* x){
	//ponteiros auxiliares
	node* y = x->getRight();
	node* b = y->getLeft();
	
	//define a subárvore enraizada por b como
	// sendo a nova subárvore direita de x
	x->setRight(b);
	
	//coloca a nova subárvore enraizada por
	// x como subárvore esquerda de y
	y->setLeft(x);
	x->setP(y);
	
	//ajusta o pai de b
	if(b != NULL)
		b->setP(y->getLeft());
	
	//retorna y
	return y;
}

//realiza rotação esquerda-direita no nó informado
node* avlTree::leftRightRot(node* z){	
	//faz rotação à esquerda no filho esquerdo de z
	node* x = z->getLeft();
	node* y = this->leftRot(x);
	z->setLeft(y);
	y->setP(z);
	
	//faz rotação à direita em z
	node* w = this->rightRot(z);
	
	//retorna w
	return w;
}

//realiza rotação direita-esquerda no nó informado
node* avlTree::rightLeftRot(node* z){
	//faz rotação à direita no filho direito de z
	node* x = z->getRight();
	node* y = this->rightRot(x);
	z->setRight(y);
	y->setP(z);
	
	//faz rotação à esquerda em z
	node* w = this->leftRot(z);
	
	//retorna w
	return w;
}

//remove um nó da árvore e verifica se realiza as devidas rotações
// (caso sejam necessárias) para manter o balanceamento
bool avlTree::remove(node* z){	
	//se o nó for nulo ou se ele não pertencer à árvore não fará nada
	if((z == NULL) or (!this->search(z->getKey())))
		return false;
	
	//ponteiro auxiliar para o pai de z
	node* db = z->getP();
	
	//se o nó não possuir filho à esquerda
	if(z->getLeft() == NULL)
		this->transplant(z, z->getRight()); //substitui pela subárvore direita
	//se o nó não possuir filho à direita 
	else if(z->getRight() == NULL)
		this->transplant(z, z->getLeft()); //substitui pela subárvore esquerda
	//o nó a ser removido possui os dois filhos
	else{
		//encontra o menor elemento da subárvore direita do nó a ser removido
		node* y = this->getMinimum(z->getRight());
		db = y->getP();
		
		//verifica se o menor elemento não está diretamente
		// à direita do elemento a ser removido
		if(y != z->getRight()){
			//transplanta a subárvore à direita do menor elemento no lugar dele
			this->transplant(y, y->getRight());
			//transfere a subárvore direita do nó a ser removido para y
			y->setRight(z->getRight());
			y->getRight()->setP(y);
			z->setRight(NULL);
		}
		//coloca a subárvore enraizada por y no lugar do nó a ser removido
		this->transplant(z, y);
		//transfere a subárvore esquerda do nó removido para y
		y->setLeft(z->getLeft());
		y->getLeft()->setP(y);
		z->setLeft(NULL);
		z->setRight(NULL);
	}
	
	//verifica o balanceamento da árvore após a remoção
	if(db != NULL)
		this->rebalance(db);
	
	//finaliza a remoção
	return true;
}

//retorna um ponteiro para o nó que é raiz da árvore
node* avlTree::getRoot(){
	return this->root;
}

//retorna um ponteiro para o menor valor
// da árvore enraizada pelo nó informado
node* avlTree::getMinimum(node* x){
	if (x == NULL)
		return NULL;

	//ponteiro auxiliar
	node* min = x;
	
	//encontra e retorna um ponteiro
	// para o nó mais a esquerda
	while(min->getLeft() != NULL)
		min = min->getLeft();
	
	return min;
}

//retorna um ponteiro para o maior valor
// da árvore enraizada pelo nó informado
node* avlTree::getMaximum(node* x){
	if (x == NULL)
		return NULL;

	//ponteiro auxiliar
	node* max = x;
	
	//encontra e retorna um ponteiro
	// para o nó mais a direita
	while(max->getRight() != NULL)
		max = max->getRight();
	return max;
}

//coloca a subárvore enraizada por "v" no lugar
// lugar da subárvore enraizada por "u"
void avlTree::transplant(node* u, node* v){
	//verifica se "u" é raiz
	if(u->getP() == NULL)
		this->root = v;
	//se "u" não for raiz
	else
		//identifica se "u" é filho esquerdo ou direito e define
		// "v" como novo filho do nó que era pai de "u"
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
