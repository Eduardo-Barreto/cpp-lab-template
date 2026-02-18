#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(DivisaoInteiraVsFloat, ResultadoCorreto) {
    auto result = run("divisao-inteira-vs-float");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("3.5"), std::string::npos)
        << "Deve conter 3.5 (resultado da divisao float)";
}
