#include "CppUnitTest.h"
#include "avlTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//testes unitários da árvore AVL
namespace UnitTestTree
{
	//testes de remoção
	TEST_CLASS(Removal)
	{
		//remoção de nós folhas
		TEST_METHOD(removeLeaf)
		{
			//cria os nós e os insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			node seis(42, NULL, NULL, NULL);
			node sete(76, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//solicita a remoção e confirma que foi bem sucedida
			Assert::IsTrue(arvore.remove(&quatro));
			Assert::IsFalse(arvore.search(17));
			Assert::IsNull(dois.getLeft());

			//solicita a remoção e confirma que foi bem sucedida
			Assert::IsTrue(arvore.remove(&cinco));
			Assert::IsFalse(arvore.search(91));
			Assert::IsNull(tres.getRight());
		}

		//remoção de elemento inexistente
		TEST_METHOD(removeFalse)
		{
			//cria uma árvore vazia
			avlTree arvore;
			//cria nós mas não os insere na árvore
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);

			//tenta remover o elmento 63 da árvore vazia
			Assert::IsFalse(arvore.remove(&um));

			//insere os nós na árvore
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);

			//tenta remover o elemento 17 que não está na árvore
			Assert::IsFalse(arvore.search(17));
			Assert::IsFalse(arvore.remove(&quatro));
		}

		//remoção comum sem necessidade de balanceamento
		TEST_METHOD(removeCommon)
		{
			//cria nós e os insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			node seis(42, NULL, NULL, NULL);
			node sete(76, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//realiza e confirma a remoção do elemento 29
			arvore.remove(&dois);
			Assert::IsFalse(arvore.search(29));
			//confirma se os ponteiros estão corretos após a remoção
			Assert::IsTrue(um.getLeft() == &seis);
			Assert::IsTrue(seis.getP() == &um);
			Assert::IsNull(seis.getRight());
			Assert::IsTrue(seis.getLeft() == &quatro);
			Assert::IsTrue(quatro.getP() == &seis);

			//realiza e confirma a remoção do elemento 85
			arvore.remove(&tres);
			Assert::IsFalse(arvore.search(85));
			//confirma se os ponteiros estão corretos após a remoção
			Assert::IsTrue(um.getRight() == &cinco);
			Assert::IsTrue(cinco.getP() == &um);
			Assert::IsNull(cinco.getRight());
			Assert::IsTrue(cinco.getLeft() == &sete);
			Assert::IsTrue(sete.getP() == &cinco);
		}	
		
		//remoção com necessidade de rotação à esquerda
		TEST_METHOD(removeLeftRotation)
		{
			//cria e insere elementos na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(91, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);

			//realiza e confirma a remoção do elemento 29
			arvore.remove(&dois);
			Assert::IsFalse(arvore.search(29));
			//confirma se os ponteiros estão corretos e se a rotação à esquerda foi realizada
			Assert::IsNull(um.getRight());
			Assert::IsNull(um.getLeft());
			Assert::IsTrue(um.getP() == &tres);
			Assert::IsTrue(tres.getLeft() == &um);
			Assert::IsNull(tres.getP());
			Assert::IsTrue(tres.getRight() == &quatro);
		}

		//remoção com necessidade de rotação à direita
		TEST_METHOD(removeRightRotation)
		{
			//cria e insere elementos na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);

			//realiza e confirma a remoção do elemento 85
			arvore.remove(&tres);
			Assert::IsFalse(arvore.search(85));
			//confirma se os ponteiros estão corretos e se a rotação à direita foi realizada
			Assert::IsNull(um.getRight());
			Assert::IsNull(um.getLeft());
			Assert::IsTrue(um.getP() == &dois);
			Assert::IsTrue(dois.getLeft() == &quatro);
			Assert::IsNull(dois.getP());
			Assert::IsTrue(dois.getRight() == &um);
		}

		//remoção com necessidad de rotação esquerda-direita
		TEST_METHOD(removeLeftRightRotation)
		{
			//cria elementos e os insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(82, NULL, NULL, NULL);
			node seis(91, NULL, NULL, NULL);
			node sete(83, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//realiza e confirma a remoção do elemento 91
			arvore.remove(&seis);
			Assert::IsFalse(arvore.search(91));
			//confirma se os ponteiros estão corretos e se a rotação esquerda-direita foi realizada
			Assert::IsTrue(um.getRight() == &sete);
			Assert::IsTrue(sete.getP() == &um);
			Assert::IsTrue(sete.getLeft() == &cinco);
			Assert::IsTrue(sete.getRight() == &tres);
			Assert::IsTrue(cinco.getP() == &sete);
			Assert::IsTrue(tres.getP() == &sete);
		}

		//remoção com necessidade de rotação direita-esquerda
		TEST_METHOD(removeRightLeftRotation)
		{
			//cria e insere elementos na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(91, NULL, NULL, NULL);
			node cinco(17, NULL, NULL, NULL);
			node seis(33, NULL, NULL, NULL);
			node sete(31, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//realiza e confirma a remoção do elemento 17
			arvore.remove(&cinco);
			Assert::IsFalse(arvore.search(17));
			//confirma se os ponteiros estão corretos e se a rotação direita-esquerda foi realizada
			Assert::IsTrue(um.getLeft() == &sete);
			Assert::IsTrue(sete.getP() == &um);
			Assert::IsTrue(sete.getLeft() == &dois);
			Assert::IsTrue(sete.getRight() == &seis);
			Assert::IsTrue(dois.getP() == &sete);
			Assert::IsTrue(seis.getP() == &sete);
		}
	};

	//testes de métodos getters
	TEST_CLASS(Getters)
	{
		//testa o retorno da raíz da árvore
		TEST_METHOD(getRoot)
		{
			//declara a árvore vazia e confirma que a raíz é nula
			avlTree arvore;
			Assert::IsNull(arvore.getRoot());

			//declara e insere elementos na árvore
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			//verifica o retorno da nova raíza da árvore (63)
			Assert::IsTrue(arvore.getRoot() == &um);
		}

		//testa o retorno do maior elemento da árvore
		TEST_METHOD(getMax)
		{
			//cria árvore vazia e confirma maior elemento nulo
			avlTree arvore;
			Assert::IsNull(arvore.getMaximum(arvore.getRoot()));

			//cria e insere elementos na árvore
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			node seis(42, NULL, NULL, NULL);
			node sete(76, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//confirma que o maior elemento encontrado foi o 91
			Assert::AreEqual(arvore.getMaximum(arvore.getRoot())->getKey(), 91);
		}

		//teste de retorno do menor elemento da árvore
		TEST_METHOD(getMin)
		{
			//cria árvore vazia e confirma menor elemento nulo
			avlTree arvore;
			Assert::IsNull(arvore.getMinimum(arvore.getRoot()));
			
			//declara e insere elementos na árvore 
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			node seis(42, NULL, NULL, NULL);
			node sete(76, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//confirma que o menor elemento encontrado foi 17
			Assert::AreEqual(arvore.getMinimum(arvore.getRoot())->getKey(), 17);
		}
	};

	//testes de busca
	TEST_CLASS(Search)
	{
		//busca com retorno true/false
		TEST_METHOD(searchNode)
		{
			//cria e insere elementos na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			node seis(42, NULL, NULL, NULL);
			node sete(76, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//testa busca de elemento inexistente
			Assert::IsFalse(arvore.search(27));
			//testa busca de elemento existente
			Assert::IsTrue(arvore.search(76));
		}

		//busca com retorno de ponteiro para elemento encontrado
		TEST_METHOD(searchNodePtr)
		{
			//cria e insere elementos na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			node seis(42, NULL, NULL, NULL);
			node sete(76, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);

			//busca elemento inexistente e confirma resultado nulo
			Assert::IsNull(arvore.searchPointer(27));
			//busca e confirma existência do elemento 76
			Assert::AreEqual(arvore.searchPointer(76)->getKey(), 76);
		}
	};

	//teste de construtores
	TEST_CLASS(Constructors)
	{
		//teste de construtor vazio
		TEST_METHOD(newArvoreEmpty)
		{
			//cria árvore vazia e confirma raíz nula
			avlTree arvore;
			Assert::IsNull(arvore.getRoot());
		}

		//teste de construtor com argumento
		TEST_METHOD(newArvoreNode)
		{
			//cria árvore informando sua raíz
			node aux(17, NULL, NULL, NULL);
			avlTree arvore(&aux);
			//confirma que a raíz da árvore é a mesma fornecida no construtor
			Assert::IsTrue(arvore.getRoot() == &aux);
		}
	};

	//teste de métodos auxiliares
	TEST_CLASS(Assistants)
	{
		//teste do método transplante
		TEST_METHOD(transplant)
		{
			//cria elementos e insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);

			//cria elementos e efetua ligação de árvore de forma manual
			node quatro(77, NULL, NULL, NULL);
			node cinco(75, NULL, NULL, NULL);
			node seis(79, NULL, NULL, NULL);
			quatro.setLeft(&cinco);
			quatro.setRight(&seis);
			cinco.setP(&quatro);
			seis.setP(&quatro);

			//transplanta árvore manual para árvore original
			arvore.transplant(&tres, &quatro);

			//confirma que os ponteiros estão corretos
			Assert::IsTrue(um.getRight() == &quatro);
			Assert::IsTrue(quatro.getP() == &um);
		}
	};

	//testes de inserção
	TEST_CLASS(Insertion)
	{
	public:
		//inserção em árvore vazia
		TEST_METHOD(insertionEmptyTree)
		{
			//cria árvore vazia
			avlTree arvore;
			node aux(16, NULL, NULL, NULL);
			//insere elemento e confirma que ele se tornou a raíz
			arvore.insert(aux);
			Assert::IsTrue(arvore.getRoot() == &aux);
		}

		//inserção comum sem necessidade de balanceamento
		TEST_METHOD(insertionCommom)
		{
			//cria elementos e insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);

			//confirma que os elementos foram inseridos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			//verifica se ponteiros estão corretos
			Assert::IsTrue(tres.getP() == &um);
			Assert::IsTrue(dois.getP() == &um);
			Assert::IsNull(tres.getLeft());
			Assert::IsNull(tres.getRight());
			Assert::IsNull(dois.getLeft());
			Assert::IsNull(dois.getRight());
		}

		//inserção com necessidade de rotação à direita
		TEST_METHOD(insertionRightRotation)
		{
			//cria elementos e insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(15, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);

			//confirma inserção dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(17));
			Assert::IsTrue(arvore.search(15));
			//confirma se ponteiros estão corretos e se a rotação à direita foi realizada
			Assert::IsTrue(um.getLeft() == &quatro);
			Assert::IsTrue(quatro.getP() == &um);
			Assert::IsTrue(quatro.getLeft() == &cinco);
			Assert::IsTrue(quatro.getRight() == &dois);
			Assert::IsTrue(cinco.getP() == &quatro);
			Assert::IsTrue(dois.getP() == &quatro);
			Assert::IsNull(cinco.getLeft());
			Assert::IsNull(cinco.getRight());
			Assert::IsNull(dois.getLeft());
			Assert::IsNull(dois.getRight());
		}

		//inserção com necssidade de rotação à esquerda
		TEST_METHOD(insertionLeftRotation)
		{
			//cria elementos e insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(87, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);

			//confirma inserção dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(87));
			Assert::IsTrue(arvore.search(91));
			//confirma se ponteiros estão corretos e se foi realizada a rotação à esquerda
			Assert::IsTrue(um.getRight() == &quatro);
			Assert::IsTrue(quatro.getP() == &um);
			Assert::IsTrue(quatro.getLeft() == &tres);
			Assert::IsTrue(quatro.getRight() == &cinco);
			Assert::IsTrue(cinco.getP() == &quatro);
			Assert::IsTrue(tres.getP() == &quatro);
			Assert::IsNull(cinco.getLeft());
			Assert::IsNull(cinco.getRight());
			Assert::IsNull(tres.getLeft());
			Assert::IsNull(tres.getRight());
		}

		//inserção com necessidade de rotação direita-esquerda
		TEST_METHOD(insertionRightLeftRotation)
		{
			//cria e insere elementos na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(33, NULL, NULL, NULL);
			node cinco(31, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);

			//confirma inserção dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(33));
			Assert::IsTrue(arvore.search(31));
			//confirma se ponteiros estão corretos e se foi realizada a rotação direita-esquerda
			Assert::IsTrue(um.getLeft() == &cinco);
			Assert::IsTrue(cinco.getP() == &um);
			Assert::IsTrue(cinco.getLeft() == &dois);
			Assert::IsTrue(cinco.getRight() == &quatro);
			Assert::IsTrue(dois.getP() == &cinco);
			Assert::IsTrue(quatro.getP() == &cinco);
			Assert::IsNull(dois.getLeft());
			Assert::IsNull(dois.getRight());
			Assert::IsNull(quatro.getLeft());
			Assert::IsNull(quatro.getRight());
		}

		//inserção com necessidade de rotação esquerda-direita
		TEST_METHOD(insertionLeftRightRotation)
		{
			//cria elementos e insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(83, NULL, NULL, NULL);
			node cinco(84, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);

			//confirma inserção dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(83));
			Assert::IsTrue(arvore.search(84));
			//confirma se ponteiros estão corretos e se foi realizada a rotação esquerda-direita
			Assert::IsTrue(um.getRight() == &cinco);
			Assert::IsTrue(cinco.getP() == &um);
			Assert::IsTrue(cinco.getLeft() == &quatro);
			Assert::IsTrue(cinco.getRight() == &tres);
			Assert::IsTrue(tres.getP() == &cinco);
			Assert::IsTrue(quatro.getP() == &cinco);
			Assert::IsNull(tres.getLeft());
			Assert::IsNull(tres.getRight());
			Assert::IsNull(quatro.getLeft());
			Assert::IsNull(quatro.getRight());
		}
	};
}

//testes unitários dos nós
namespace UnitTestNode
{
	//testes de métodos getters
	TEST_CLASS(Getters)
	{
		//teste de retorno do nó pai
		TEST_METHOD(getFather)
		{
			//declara nós sendo aux4 filho de aux1
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, &aux1, NULL, NULL);
			aux1.setLeft(&aux4);
			//condirma aux4 reconhece seu pai
			Assert::IsTrue(aux4.getP() == &aux1);
		}

		//teste de retorno de filho esquerdo
		TEST_METHOD(getLeftChild)
		{
			//declara nós sendo aux1 filho esquerdo de aux4
			node aux1(17, NULL, NULL, NULL);
			node aux4(78, NULL, &aux1, NULL);
			aux1.setP(&aux4);
			//confirma que aux4 reconhece seu filho esquerdo
			Assert::IsTrue(aux4.getLeft() == &aux1);
		}

		//teste de retorno de filho direito
		TEST_METHOD(getRightChild)
		{
			//declara nós sendo aux1 filho direito de aux4
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, NULL, NULL, &aux1);
			aux1.setP(&aux4);
			//confirma que aux4 reconhece seu filho direito
			Assert::IsTrue(aux4.getRight() == &aux1);
		}

		//teste dr retorno do valor da chave
		TEST_METHOD(getKey)
		{
			//declara nó e confirma que ele reconhece o valor de sua chave
			node aux1(78, NULL, NULL, NULL);
			Assert::AreEqual(aux1.getKey(), 78);
		}

		//teste de retorno do fator de balanço
		TEST_METHOD(getBalance)
		{
			//cria elementos e insere na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);

			//confirma fator de balanço esperado para os elementos 63 e 85
			Assert::AreEqual(um.getBalance(), 1);
			Assert::AreEqual(tres.getBalance(), 0);
			//insere novo elemento
			arvore.insert(cinco);
			//confirma fatores atualizados
			Assert::AreEqual(um.getBalance(), 0);
			Assert::AreEqual(tres.getBalance(), -1);
		}

		//teste de retorno da altura
		TEST_METHOD(getHeight)
		{
			//cria e insere elementos na árvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			node cinco(91, NULL, NULL, NULL);
			node seis(42, NULL, NULL, NULL);
			node sete(76, NULL, NULL, NULL);
			node oito(45, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);
			arvore.insert(cinco);
			arvore.insert(seis);
			arvore.insert(sete);
			arvore.insert(oito);
			//confirma a altura de todos os elementos
			Assert::AreEqual(um.getHeight(), 3);
			Assert::AreEqual(dois.getHeight(), 2);
			Assert::AreEqual(tres.getHeight(), 1);
			Assert::AreEqual(quatro.getHeight(), 0);
			Assert::AreEqual(cinco.getHeight(), 0);
			Assert::AreEqual(seis.getHeight(), 1);
			Assert::AreEqual(sete.getHeight(), 0);
			Assert::AreEqual(oito.getHeight(), 0);
		}
	};

	//testes de construtor
	TEST_CLASS(Constructor)
	{
		//construtor com argumentos
		TEST_METHOD(constructor)
		{
			//cria elementos passando os devidos argumentos
			node aux1(63, NULL, NULL, NULL);
			node aux2(75, NULL, NULL, NULL);
			node aux3(91, NULL, NULL, NULL);
			node aux4(78, &aux1, &aux2, &aux3);
			//confirma que parâmetros do construtor foram passados à aux4 corretamente
			Assert::AreEqual(aux4.getKey(), 78);
			Assert::IsTrue(aux4.getP() == &aux1);
			Assert::IsTrue(aux4.getLeft() == &aux2);
			Assert::IsTrue(aux4.getRight() == &aux3);
		}
	};

	//testes de setters
	TEST_CLASS(Setters)
	{
		//teste de definição do nó pai
		TEST_METHOD(setFather)
		{
			//cria elementos
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, NULL, NULL, NULL);
			//define aux1 como pai de aux4 e confirma alteração
			aux4.setP(&aux1);
			Assert::IsTrue(aux4.getP() == &aux1);
		}

		//teste de definição do filho esquerdo
		TEST_METHOD(setLeftChild)
		{
			//cria elementos
			node aux1(72, NULL, NULL, NULL);
			node aux4(75, NULL, NULL, NULL);
			//define aux1 como filho esquerdo de aux4 e confirma alteração
			aux4.setLeft(&aux1);
			Assert::IsTrue(aux4.getLeft() == &aux1);
		}

		//teste definição de filho direito
		TEST_METHOD(setRightChild)
		{
			//cria elementos
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, NULL, NULL, NULL);
			//define aux1 como filho direito de aux4 e confirma alteração
			aux4.setRight(&aux1);
			Assert::IsTrue(aux4.getRight() == &aux1);
		}

		//teste definição de chave
		TEST_METHOD(setKey)
		{
			//cria elemento
			node aux1(78, NULL, NULL, NULL);
			//define o novo valor da chave e confirma alteração
			aux1.setKey(63);
			Assert::IsTrue(aux1.getKey() == 63);
		}
	};
}