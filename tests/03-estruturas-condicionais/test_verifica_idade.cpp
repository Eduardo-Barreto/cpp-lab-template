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

TEST(VerificaIdade, MaiorDeIdade) {
    auto result = run("verifica-idade", "25\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("maior"), std::string::npos);
}

TEST(VerificaIdade, MenorDeIdade) {
    auto result = run("verifica-idade", "15\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("menor"), std::string::npos);
}

TEST(VerificaIdade, Limite18) {
    auto result = run("verifica-idade", "18\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("maior"), std::string::npos);
}
