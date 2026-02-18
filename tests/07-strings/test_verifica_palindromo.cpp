#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "helpers/subprocess.hpp"

namespace {

std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

}  // namespace

TEST(VerificaPalindromo, EhPalindromo) {
    auto result = run("verifica-palindromo", "arara\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("palindromo"), std::string::npos);
    EXPECT_EQ(output.find("nao"), std::string::npos);
}

TEST(VerificaPalindromo, NaoEhPalindromo) {
    auto result = run("verifica-palindromo", "hello\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("nao"), std::string::npos);
}

TEST(VerificaPalindromo, ComMaiusculas) {
    auto result = run("verifica-palindromo", "Ana\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("palindromo"), std::string::npos);
    EXPECT_EQ(output.find("nao"), std::string::npos);
}
