#include <gtest/gtest.h>

#include "helpers/subprocess.hpp"

TEST(PadraoAsteriscos, ImprimePadrao) {
    auto result = run("padrao-asteriscos");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "*\n**\n***\n****\n*****\n");
}
