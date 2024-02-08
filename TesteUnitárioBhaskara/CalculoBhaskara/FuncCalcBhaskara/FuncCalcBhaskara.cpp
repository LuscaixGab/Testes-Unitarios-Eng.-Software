#ifndef FuncBhaskara_cpp
#define FuncBhaskara_cpp

//bibliotecas
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

//função para cálculo dos valores de x pela fórmula de bhaskara
bool calcBhaskara(double A, double B, double C, double& delta, double& x1, double& x2) {
    //cálculo do delta
    delta = (B * B) - (4 * A * C);
    //verifica se a função possui raizes reais
    if (delta < 0)
        return false;//não possui raizes reais
    //calcula as raizes da equação
    x1 = ((B * (-1)) + (sqrt(delta))) / (2 * A);
    x2 = ((B * (-1)) - (sqrt(delta))) / (2 * A);
    return true; //possui raizes reais
}

#endif
