#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ComprimentoString, PalavraSimples) {
    auto result = run("comprimento-string", "hello\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find('5'), std::string::npos);
}

TEST(ComprimentoString, Frase) {
    auto result = run("comprimento-string", "ola mundo\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find('9'), std::string::npos);
}
