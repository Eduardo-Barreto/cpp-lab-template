#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "helpers/subprocess.hpp"

TEST(DadosPessoais, ImprimeDuasLinhas) {
    auto result = run("dados-pessoais");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());

    auto newlines = std::count(result.stdout_output.begin(), result.stdout_output.end(), '\n');
    EXPECT_GE(newlines, 2) << "Deve imprimir pelo menos duas linhas (nome e curso)";
}
