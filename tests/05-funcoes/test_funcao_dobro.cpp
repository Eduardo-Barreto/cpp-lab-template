#include <gtest/gtest.h>

#include "helpers/subprocess.hpp"

TEST(FuncaoDobro, Positivo) {
    auto result = run("funcao-dobro", "5\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "10\n");
}

TEST(FuncaoDobro, Zero) {
    auto result = run("funcao-dobro", "0\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "0\n");
}

TEST(FuncaoDobro, Negativo) {
    auto result = run("funcao-dobro", "-3\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "-6\n");
}
