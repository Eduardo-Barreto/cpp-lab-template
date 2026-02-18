#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ClasseContaBancaria, OperacoesBasicas) {
    auto result = run("classe-conta-bancaria");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());
}
