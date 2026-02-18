#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(SomaDiagonal, MatrizSimples) {
    auto result = run("soma-diagonal", "1\n2\n3\n4\n5\n6\n7\n8\n9\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("15"), std::string::npos);
}

TEST(SomaDiagonal, MatrizZeros) {
    auto result = run("soma-diagonal", "0\n0\n0\n0\n0\n0\n0\n0\n0\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find('0'), std::string::npos);
}
