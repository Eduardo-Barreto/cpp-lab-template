#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ClassePessoa, ImprimeDuasPessoas) {
    auto result = run("classe-pessoa");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());

    auto first = result.stdout_output.find('\n');
    EXPECT_NE(first, std::string::npos);
}
