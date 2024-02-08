//bibliotecas
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "FuncCalcBhaskara.cpp"

using namespace std;

//função principal
int main()
{
    //variáveis locais
    double A = 0, B = 0, C = 0;
    double delta = 0;
    double x1 = 0, x2 = 0;
    //coleta os valores de A, B e C
    cout << "Informe o valor de A: ";
    cin >> A;
    cout << "Informe o valor de B: ";
    cin >> B;
    cout << "Informe o valor de C: ";
    cin >> C;
    //apresenta os resultados (caso a equação possua raizes reais)
    if (calcBhaskara(A, B, C, delta, x1, x2)) {
        cout << endl << "O valor de delta eh: " << delta << endl;
        cout << "O valor de x1 eh: " << x1 << endl;;
        cout << "O valor de x2 eh: " << x2 << endl;
    }
    //informa que a equação não possui raizes reais
    else {
        cout << endl << "Delta NEGATIVO (" << delta << ") - Nao eh possivel encontrar os valores de X" << endl;
    }
    //finaliza o programa
    return 0;
}