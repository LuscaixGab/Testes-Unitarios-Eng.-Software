#include "CppUnitTest.h"
#include "FuncCalcBhaskara.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//unidade de testes
namespace UnitTest2
{
	//classe de testes
	TEST_CLASS(CalcBhaskaraFunction)
	{
	public:
		//teste da função
		TEST_METHOD(Bhaskara)
		{
			//define os valores das variáveis
			double A = 1;
			double B = -5;
			double C = 6;
			double delta = 0;
			double x1 = 0, x2 = 0;
			//executa a função e confirma que as raizes existem
			Assert::IsTrue(calcBhaskara(A, B, C, delta, x1, x2));
			//compara os valores de delta e das raizes de x com o esperado
			Assert::AreEqual(delta, 1.0);
			Assert::AreEqual(x1, 3.0);
			Assert::AreEqual(x2, 2.0);
			//define novos valores para as variaveis
			A = 1;
			B = 4;
			C = 5;
			//executa a função e confirma que não existem raizes reais
			Assert::IsFalse(calcBhaskara(A, B, C, delta, x1, x2));
			//compara o valor de delta com o esperado
			Assert::AreEqual(delta, -4.0);
		}
	};
}
