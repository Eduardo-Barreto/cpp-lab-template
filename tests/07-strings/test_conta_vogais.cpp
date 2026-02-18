#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ContaVogais, PalavraComVogais) {
    auto result = run("conta-vogais", "abacate\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("4"), std::string::npos);
}

TEST(ContaVogais, SemVogais) {
    auto result = run("conta-vogais", "bcd\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("0"), std::string::npos);
}
