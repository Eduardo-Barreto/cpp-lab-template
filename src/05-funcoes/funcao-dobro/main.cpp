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

namespace {
int dobro(int num) {
    return num * 2;
}
} // namespace

int main() {
      int num;
    cin >> num;
    cout << dobro(num) << '\n';
    return 0;
}
