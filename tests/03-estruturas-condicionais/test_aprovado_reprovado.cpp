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

TEST(AprovadoReprovado, Aprovado) {
    auto result = run("aprovado-reprovado", "8.5\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("aprovado"), std::string::npos);
}

TEST(AprovadoReprovado, Reprovado) {
    auto result = run("aprovado-reprovado", "4.0\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("reprovado"), std::string::npos);
}

TEST(AprovadoReprovado, NotaLimite) {
    auto result = run("aprovado-reprovado", "6.0\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("aprovado"), std::string::npos);
}
