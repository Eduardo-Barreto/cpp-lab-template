#include <gtest/gtest.h>

#include <cstdlib>

#include "helpers/subprocess.hpp"

TEST(SomaDoisNumeros, ImprimeSoma) {
    auto result = run("soma-dois-numeros");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());

    const int valor = std::atoi(result.stdout_output.c_str());
    EXPECT_NE(result.stdout_output, "0\n") << "A soma nao pode ser zero — atribua valores reais as variaveis";
    EXPECT_NE(valor, 0) << "O programa deve imprimir um numero inteiro (a soma)";
}
