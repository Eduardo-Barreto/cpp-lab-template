/**
 * @file main.cpp
 * @brief Funcao Dobro
 *
 * Escreva uma funcao em C++ chamada `dobro` que receba um numero inteiro
 * como parametro e retorne o dobro desse numero. No programa principal,
 * leia um numero, chame a funcao e imprima o resultado.
 */

#include <iostream>
using namespace std;

int dobro(int n) {
    return n * 2;
}

int main() {
    int n;
    cin >> n;
    cout << dobro(n) << endl;
    return 0;
}
