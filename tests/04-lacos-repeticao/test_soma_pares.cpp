#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(SomaPares, ResultadoCorreto) {
    auto result = run("soma-pares");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("2550"), std::string::npos);
}
