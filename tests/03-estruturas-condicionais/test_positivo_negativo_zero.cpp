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

TEST(PositivoNegativoZero, Positivo) {
    auto result = run("positivo-negativo-zero", "7\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("positivo"), std::string::npos);
}

TEST(PositivoNegativoZero, Negativo) {
    auto result = run("positivo-negativo-zero", "-3\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("negativo"), std::string::npos);
}

TEST(PositivoNegativoZero, Zero) {
    auto result = run("positivo-negativo-zero", "0\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("zero"), std::string::npos);
}
