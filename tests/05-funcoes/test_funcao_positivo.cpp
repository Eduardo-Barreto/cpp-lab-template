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

TEST(FuncaoPositivo, NumeroPositivo) {
    auto result = run("funcao-positivo", "5\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_TRUE(output.find("true") != std::string::npos || output.find("verdadeir") != std::string::npos ||
                output.find("positivo") != std::string::npos || output.find("sim") != std::string::npos ||
                output.find("1") != std::string::npos);
}

TEST(FuncaoPositivo, NumeroNegativo) {
    auto result = run("funcao-positivo", "-3\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_TRUE(output.find("false") != std::string::npos || output.find("falso") != std::string::npos ||
                output.find("negativo") != std::string::npos || output.find("nao") != std::string::npos ||
                output.find("0") != std::string::npos);
}

TEST(FuncaoPositivo, Zero) {
    auto result = run("funcao-positivo", "0\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_TRUE(output.find("false") != std::string::npos || output.find("falso") != std::string::npos ||
                output.find("nao") != std::string::npos || output.find("0") != std::string::npos);
}
