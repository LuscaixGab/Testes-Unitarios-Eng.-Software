/*
OBSERVA��ES DO PROGRAMA
1. A forma como os n�s s�o apresentados na impress�o
   preoerder, inorder e postorder podem ser alterados
   na linha 17, modificando o valor de "mode".
2. Se o valor de "mode" for 1 (impress�o detalhada),
   � necess�rio dar um "enter" para que ele imprima o
   pr�ximo n�.
*/

//bibliotecas
#include <cstdio>
#include <iostream>

#include "node.cpp"
#include "avlTree.cpp"

using namespace std;

//define se todos dados dos n�s ser�o impressos ou apenas as chaves
// ('0' para apenas as chaves e '1' para informa��es detalhadas)
#define mode 1

//prot�tipos
void inorderTreeWalk(node*);
void inorderPrintNodeWalk(node*);
void preorderTreeWalk(node*);
void preorderPrintNodeWalk(node*);
void postorderTreeWalk(node*);
void postorderPrintNodeWalk(node*);

//fun��o principal
int main() {
	//cria uma �rvore
	avlTree arvore;

	//cria e inicializa alguns n�s
	node um(45, NULL, NULL, NULL);
	node dois(12, NULL, NULL, NULL);
	node tres(78, NULL, NULL, NULL);
	node quatro(23, NULL, NULL, NULL);
	node cinco(56, NULL, NULL, NULL);
	node seis(91, NULL, NULL, NULL);
	node sete(34, NULL, NULL, NULL);
	node oito(67, NULL, NULL, NULL);
	node nove(19, NULL, NULL, NULL);
	node dez(82, NULL, NULL, NULL);
	node onze(30, NULL, NULL, NULL);
	node doze(73, NULL, NULL, NULL);
	node treze(15, NULL, NULL, NULL);
	node quatorze(68, NULL, NULL, NULL);
	node quinze(40, NULL, NULL, NULL);
	node dezesseis(87, NULL, NULL, NULL);
	node dezessete(25, NULL, NULL, NULL);
	node dezoito(27, NULL, NULL, NULL);
	node dezenove(2, NULL, NULL, NULL);
	node vinte(17, NULL, NULL, NULL);

	//insere os n�s na �rvore
	cout << "Inserindo elementos..." << endl;
	arvore.insert(um);
	arvore.insert(dois);
	arvore.insert(tres);
	arvore.insert(quatro);
	arvore.insert(cinco);
	arvore.insert(seis);
	arvore.insert(sete);
	arvore.insert(oito);
	arvore.insert(nove);
	arvore.insert(dez);
	arvore.insert(onze);
	arvore.insert(doze);
	arvore.insert(treze);
	arvore.insert(quatorze);
	arvore.insert(quinze);
	arvore.insert(dezesseis);
	arvore.insert(dezessete);

	//imprime cada um os n�s da �rvore em preorder
	if (mode == 1)
		preorderPrintNodeWalk(arvore.getRoot()); //imprime dados detalhados
	else if (mode == 0)
		preorderTreeWalk(arvore.getRoot()); //imprime apenas a chave

	getchar();

	//remove alguns elementos da �rvore
	cout << "Removendo alguns elementos..." << endl;
	arvore.remove(&um);
	arvore.remove(&dezesseis);
	arvore.remove(&nove);
	arvore.remove(&quinze);
	arvore.remove(&tres);

	//imprime cada um os n�s da �rvore em inorder
	if (mode == 1)
		inorderPrintNodeWalk(arvore.getRoot()); //imprime dados detalhados
	else if (mode == 0)
		inorderTreeWalk(arvore.getRoot()); //imprime apenas a chave

	getchar();

	//insere novos n�s na �rvore
	cout << "Inserindo novos elementos..." << endl;
	arvore.insert(dezoito);
	arvore.insert(dezenove);
	arvore.insert(vinte);

	//imprime cada um os n�s da �rvore em postorder
	if (mode == 1)
		postorderPrintNodeWalk(arvore.getRoot()); //imprime dados detalhados
	else if (mode == 0)
		postorderTreeWalk(arvore.getRoot()); //imprime apenas a chave

	getchar();

	//mostra outras funcionalidades
	cout << "Informacoes adicionais..." << endl;
	cout << "RAIZ: " << arvore.getRoot()->getKey() << endl;
	cout << "MAIOR ELEMENTO: " << arvore.getMaximum(arvore.getRoot())->getKey() << endl;
	cout << "MENOR ELEMENTO: " << arvore.getMinimum(arvore.getRoot())->getKey() << endl << endl;

	//busca um determinado n� na �rvore e
	// imprime seus dados se encontrar
	int n = 1; //chave do n� a ser pesquisado
	cout << "Procurando: " << n << endl;
	node* aux = arvore.searchPointer(n);
	if (aux != NULL)
		aux->print();
	else
		cout << "Nao encontrado..." << endl;

	//finaliza o programa
	return 0;
}

//imprime as chaves de cada n� da �rvore enraizada por "x" em inorder
void inorderTreeWalk(node* x) {
	if (x != NULL) {
		inorderTreeWalk(x->getLeft()); //recursiva a esquerda
		cout << x->getKey() << endl; //imprime a chave
		inorderTreeWalk(x->getRight()); //recursiva a direita
	}
}

//imprime todas as informa��es do n� da �rvore enraizada por "x" em inorder
void inorderPrintNodeWalk(node* x) {
	if (x != NULL) {
		inorderPrintNodeWalk(x->getLeft()); //recursiva a esquerda
		x->print(); //imprime dados do n�
		getchar();
		cout << endl;
		inorderPrintNodeWalk(x->getRight()); //recursiva a direita
	}
}

//imprime as chaves de cada n� da �rvore enraizada por "x" em preorder
void preorderTreeWalk(node* x) {
	if (x != NULL) {
		cout << x->getKey() << endl; //imprime a chave
		preorderTreeWalk(x->getLeft()); //recursiva a esquerda
		preorderTreeWalk(x->getRight()); //recursiva a direita
	}
}

//imprime todas as informa��es do n� da �rvore enraizada por "x" em preorder
void preorderPrintNodeWalk(node* x) {
	if (x != NULL) {
		x->print(); //imprime dados do n�
		getchar();
		cout << endl;
		preorderPrintNodeWalk(x->getLeft()); //recursiva a esquerda
		preorderPrintNodeWalk(x->getRight()); //recursiva a direita
	}
}

//imprime as chaves de cada n� da �rvore enraizada por "x" em postorder
void postorderTreeWalk(node* x) {
	if (x != NULL) {
		postorderTreeWalk(x->getLeft()); //recusriva a esquerda
		postorderTreeWalk(x->getRight()); //recursiva a direita
		cout << x->getKey() << endl; //imprime a chave
	}
}

//imprime todas as informa��es do n� da �rvore enraizada por "x" em posorder
void postorderPrintNodeWalk(node* x) {
	if (x != NULL) {
		postorderPrintNodeWalk(x->getLeft()); //recursiva a esquerda
		postorderPrintNodeWalk(x->getRight()); //recusriva a direita
		x->print(); //imprime dados do n�
		getchar();
		cout << endl;
	}
}