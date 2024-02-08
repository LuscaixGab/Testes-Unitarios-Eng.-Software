#include "CppUnitTest.h"
#include "avlTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//testes unit�rios da �rvore AVL
namespace UnitTestTree
{
	//testes de remo��o
	TEST_CLASS(Removal)
	{
		//remo��o de n�s folhas
		TEST_METHOD(removeLeaf)
		{
			//cria os n�s e os insere na �rvore
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

			//solicita a remo��o e confirma que foi bem sucedida
			Assert::IsTrue(arvore.remove(&quatro));
			Assert::IsFalse(arvore.search(17));
			Assert::IsNull(dois.getLeft());

			//solicita a remo��o e confirma que foi bem sucedida
			Assert::IsTrue(arvore.remove(&cinco));
			Assert::IsFalse(arvore.search(91));
			Assert::IsNull(tres.getRight());
		}

		//remo��o de elemento inexistente
		TEST_METHOD(removeFalse)
		{
			//cria uma �rvore vazia
			avlTree arvore;
			//cria n�s mas n�o os insere na �rvore
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);

			//tenta remover o elmento 63 da �rvore vazia
			Assert::IsFalse(arvore.remove(&um));

			//insere os n�s na �rvore
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);

			//tenta remover o elemento 17 que n�o est� na �rvore
			Assert::IsFalse(arvore.search(17));
			Assert::IsFalse(arvore.remove(&quatro));
		}

		//remo��o comum sem necessidade de balanceamento
		TEST_METHOD(removeCommon)
		{
			//cria n�s e os insere na �rvore
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

			//realiza e confirma a remo��o do elemento 29
			arvore.remove(&dois);
			Assert::IsFalse(arvore.search(29));
			//confirma se os ponteiros est�o corretos ap�s a remo��o
			Assert::IsTrue(um.getLeft() == &seis);
			Assert::IsTrue(seis.getP() == &um);
			Assert::IsNull(seis.getRight());
			Assert::IsTrue(seis.getLeft() == &quatro);
			Assert::IsTrue(quatro.getP() == &seis);

			//realiza e confirma a remo��o do elemento 85
			arvore.remove(&tres);
			Assert::IsFalse(arvore.search(85));
			//confirma se os ponteiros est�o corretos ap�s a remo��o
			Assert::IsTrue(um.getRight() == &cinco);
			Assert::IsTrue(cinco.getP() == &um);
			Assert::IsNull(cinco.getRight());
			Assert::IsTrue(cinco.getLeft() == &sete);
			Assert::IsTrue(sete.getP() == &cinco);
		}	
		
		//remo��o com necessidade de rota��o � esquerda
		TEST_METHOD(removeLeftRotation)
		{
			//cria e insere elementos na �rvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(91, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);

			//realiza e confirma a remo��o do elemento 29
			arvore.remove(&dois);
			Assert::IsFalse(arvore.search(29));
			//confirma se os ponteiros est�o corretos e se a rota��o � esquerda foi realizada
			Assert::IsNull(um.getRight());
			Assert::IsNull(um.getLeft());
			Assert::IsTrue(um.getP() == &tres);
			Assert::IsTrue(tres.getLeft() == &um);
			Assert::IsNull(tres.getP());
			Assert::IsTrue(tres.getRight() == &quatro);
		}

		//remo��o com necessidade de rota��o � direita
		TEST_METHOD(removeRightRotation)
		{
			//cria e insere elementos na �rvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			node quatro(17, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			arvore.insert(quatro);

			//realiza e confirma a remo��o do elemento 85
			arvore.remove(&tres);
			Assert::IsFalse(arvore.search(85));
			//confirma se os ponteiros est�o corretos e se a rota��o � direita foi realizada
			Assert::IsNull(um.getRight());
			Assert::IsNull(um.getLeft());
			Assert::IsTrue(um.getP() == &dois);
			Assert::IsTrue(dois.getLeft() == &quatro);
			Assert::IsNull(dois.getP());
			Assert::IsTrue(dois.getRight() == &um);
		}

		//remo��o com necessidad de rota��o esquerda-direita
		TEST_METHOD(removeLeftRightRotation)
		{
			//cria elementos e os insere na �rvore
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

			//realiza e confirma a remo��o do elemento 91
			arvore.remove(&seis);
			Assert::IsFalse(arvore.search(91));
			//confirma se os ponteiros est�o corretos e se a rota��o esquerda-direita foi realizada
			Assert::IsTrue(um.getRight() == &sete);
			Assert::IsTrue(sete.getP() == &um);
			Assert::IsTrue(sete.getLeft() == &cinco);
			Assert::IsTrue(sete.getRight() == &tres);
			Assert::IsTrue(cinco.getP() == &sete);
			Assert::IsTrue(tres.getP() == &sete);
		}

		//remo��o com necessidade de rota��o direita-esquerda
		TEST_METHOD(removeRightLeftRotation)
		{
			//cria e insere elementos na �rvore
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

			//realiza e confirma a remo��o do elemento 17
			arvore.remove(&cinco);
			Assert::IsFalse(arvore.search(17));
			//confirma se os ponteiros est�o corretos e se a rota��o direita-esquerda foi realizada
			Assert::IsTrue(um.getLeft() == &sete);
			Assert::IsTrue(sete.getP() == &um);
			Assert::IsTrue(sete.getLeft() == &dois);
			Assert::IsTrue(sete.getRight() == &seis);
			Assert::IsTrue(dois.getP() == &sete);
			Assert::IsTrue(seis.getP() == &sete);
		}
	};

	//testes de m�todos getters
	TEST_CLASS(Getters)
	{
		//testa o retorno da ra�z da �rvore
		TEST_METHOD(getRoot)
		{
			//declara a �rvore vazia e confirma que a ra�z � nula
			avlTree arvore;
			Assert::IsNull(arvore.getRoot());

			//declara e insere elementos na �rvore
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);
			//verifica o retorno da nova ra�za da �rvore (63)
			Assert::IsTrue(arvore.getRoot() == &um);
		}

		//testa o retorno do maior elemento da �rvore
		TEST_METHOD(getMax)
		{
			//cria �rvore vazia e confirma maior elemento nulo
			avlTree arvore;
			Assert::IsNull(arvore.getMaximum(arvore.getRoot()));

			//cria e insere elementos na �rvore
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

		//teste de retorno do menor elemento da �rvore
		TEST_METHOD(getMin)
		{
			//cria �rvore vazia e confirma menor elemento nulo
			avlTree arvore;
			Assert::IsNull(arvore.getMinimum(arvore.getRoot()));
			
			//declara e insere elementos na �rvore 
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
			//cria e insere elementos na �rvore
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
			//cria e insere elementos na �rvore
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
			//busca e confirma exist�ncia do elemento 76
			Assert::AreEqual(arvore.searchPointer(76)->getKey(), 76);
		}
	};

	//teste de construtores
	TEST_CLASS(Constructors)
	{
		//teste de construtor vazio
		TEST_METHOD(newArvoreEmpty)
		{
			//cria �rvore vazia e confirma ra�z nula
			avlTree arvore;
			Assert::IsNull(arvore.getRoot());
		}

		//teste de construtor com argumento
		TEST_METHOD(newArvoreNode)
		{
			//cria �rvore informando sua ra�z
			node aux(17, NULL, NULL, NULL);
			avlTree arvore(&aux);
			//confirma que a ra�z da �rvore � a mesma fornecida no construtor
			Assert::IsTrue(arvore.getRoot() == &aux);
		}
	};

	//teste de m�todos auxiliares
	TEST_CLASS(Assistants)
	{
		//teste do m�todo transplante
		TEST_METHOD(transplant)
		{
			//cria elementos e insere na �rvore
			avlTree arvore;
			node um(63, NULL, NULL, NULL);
			node dois(29, NULL, NULL, NULL);
			node tres(85, NULL, NULL, NULL);
			arvore.insert(um);
			arvore.insert(dois);
			arvore.insert(tres);

			//cria elementos e efetua liga��o de �rvore de forma manual
			node quatro(77, NULL, NULL, NULL);
			node cinco(75, NULL, NULL, NULL);
			node seis(79, NULL, NULL, NULL);
			quatro.setLeft(&cinco);
			quatro.setRight(&seis);
			cinco.setP(&quatro);
			seis.setP(&quatro);

			//transplanta �rvore manual para �rvore original
			arvore.transplant(&tres, &quatro);

			//confirma que os ponteiros est�o corretos
			Assert::IsTrue(um.getRight() == &quatro);
			Assert::IsTrue(quatro.getP() == &um);
		}
	};

	//testes de inser��o
	TEST_CLASS(Insertion)
	{
	public:
		//inser��o em �rvore vazia
		TEST_METHOD(insertionEmptyTree)
		{
			//cria �rvore vazia
			avlTree arvore;
			node aux(16, NULL, NULL, NULL);
			//insere elemento e confirma que ele se tornou a ra�z
			arvore.insert(aux);
			Assert::IsTrue(arvore.getRoot() == &aux);
		}

		//inser��o comum sem necessidade de balanceamento
		TEST_METHOD(insertionCommom)
		{
			//cria elementos e insere na �rvore
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
			//verifica se ponteiros est�o corretos
			Assert::IsTrue(tres.getP() == &um);
			Assert::IsTrue(dois.getP() == &um);
			Assert::IsNull(tres.getLeft());
			Assert::IsNull(tres.getRight());
			Assert::IsNull(dois.getLeft());
			Assert::IsNull(dois.getRight());
		}

		//inser��o com necessidade de rota��o � direita
		TEST_METHOD(insertionRightRotation)
		{
			//cria elementos e insere na �rvore
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

			//confirma inser��o dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(17));
			Assert::IsTrue(arvore.search(15));
			//confirma se ponteiros est�o corretos e se a rota��o � direita foi realizada
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

		//inser��o com necssidade de rota��o � esquerda
		TEST_METHOD(insertionLeftRotation)
		{
			//cria elementos e insere na �rvore
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

			//confirma inser��o dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(87));
			Assert::IsTrue(arvore.search(91));
			//confirma se ponteiros est�o corretos e se foi realizada a rota��o � esquerda
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

		//inser��o com necessidade de rota��o direita-esquerda
		TEST_METHOD(insertionRightLeftRotation)
		{
			//cria e insere elementos na �rvore
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

			//confirma inser��o dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(33));
			Assert::IsTrue(arvore.search(31));
			//confirma se ponteiros est�o corretos e se foi realizada a rota��o direita-esquerda
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

		//inser��o com necessidade de rota��o esquerda-direita
		TEST_METHOD(insertionLeftRightRotation)
		{
			//cria elementos e insere na �rvore
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

			//confirma inser��o dos elementos
			Assert::IsTrue(arvore.search(63));
			Assert::IsTrue(arvore.search(29));
			Assert::IsTrue(arvore.search(85));
			Assert::IsTrue(arvore.search(83));
			Assert::IsTrue(arvore.search(84));
			//confirma se ponteiros est�o corretos e se foi realizada a rota��o esquerda-direita
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

//testes unit�rios dos n�s
namespace UnitTestNode
{
	//testes de m�todos getters
	TEST_CLASS(Getters)
	{
		//teste de retorno do n� pai
		TEST_METHOD(getFather)
		{
			//declara n�s sendo aux4 filho de aux1
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, &aux1, NULL, NULL);
			aux1.setLeft(&aux4);
			//condirma aux4 reconhece seu pai
			Assert::IsTrue(aux4.getP() == &aux1);
		}

		//teste de retorno de filho esquerdo
		TEST_METHOD(getLeftChild)
		{
			//declara n�s sendo aux1 filho esquerdo de aux4
			node aux1(17, NULL, NULL, NULL);
			node aux4(78, NULL, &aux1, NULL);
			aux1.setP(&aux4);
			//confirma que aux4 reconhece seu filho esquerdo
			Assert::IsTrue(aux4.getLeft() == &aux1);
		}

		//teste de retorno de filho direito
		TEST_METHOD(getRightChild)
		{
			//declara n�s sendo aux1 filho direito de aux4
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, NULL, NULL, &aux1);
			aux1.setP(&aux4);
			//confirma que aux4 reconhece seu filho direito
			Assert::IsTrue(aux4.getRight() == &aux1);
		}

		//teste dr retorno do valor da chave
		TEST_METHOD(getKey)
		{
			//declara n� e confirma que ele reconhece o valor de sua chave
			node aux1(78, NULL, NULL, NULL);
			Assert::AreEqual(aux1.getKey(), 78);
		}

		//teste de retorno do fator de balan�o
		TEST_METHOD(getBalance)
		{
			//cria elementos e insere na �rvore
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

			//confirma fator de balan�o esperado para os elementos 63 e 85
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
			//cria e insere elementos na �rvore
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
			//confirma que par�metros do construtor foram passados � aux4 corretamente
			Assert::AreEqual(aux4.getKey(), 78);
			Assert::IsTrue(aux4.getP() == &aux1);
			Assert::IsTrue(aux4.getLeft() == &aux2);
			Assert::IsTrue(aux4.getRight() == &aux3);
		}
	};

	//testes de setters
	TEST_CLASS(Setters)
	{
		//teste de defini��o do n� pai
		TEST_METHOD(setFather)
		{
			//cria elementos
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, NULL, NULL, NULL);
			//define aux1 como pai de aux4 e confirma altera��o
			aux4.setP(&aux1);
			Assert::IsTrue(aux4.getP() == &aux1);
		}

		//teste de defini��o do filho esquerdo
		TEST_METHOD(setLeftChild)
		{
			//cria elementos
			node aux1(72, NULL, NULL, NULL);
			node aux4(75, NULL, NULL, NULL);
			//define aux1 como filho esquerdo de aux4 e confirma altera��o
			aux4.setLeft(&aux1);
			Assert::IsTrue(aux4.getLeft() == &aux1);
		}

		//teste defini��o de filho direito
		TEST_METHOD(setRightChild)
		{
			//cria elementos
			node aux1(78, NULL, NULL, NULL);
			node aux4(17, NULL, NULL, NULL);
			//define aux1 como filho direito de aux4 e confirma altera��o
			aux4.setRight(&aux1);
			Assert::IsTrue(aux4.getRight() == &aux1);
		}

		//teste defini��o de chave
		TEST_METHOD(setKey)
		{
			//cria elemento
			node aux1(78, NULL, NULL, NULL);
			//define o novo valor da chave e confirma altera��o
			aux1.setKey(63);
			Assert::IsTrue(aux1.getKey() == 63);
		}
	};
}