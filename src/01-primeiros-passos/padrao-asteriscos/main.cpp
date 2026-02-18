/**
 * @file main.cpp
 * @brief Padrao de Asteriscos
 *
 * Escreva um programa em C++ que imprima o padrao abaixo na tela
 * usando multiplos comandos de saida:
 *
 * @code
 * *
 * **
 * ***
 * ****
 * *****
 * @endcode
 */

#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++) {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}
