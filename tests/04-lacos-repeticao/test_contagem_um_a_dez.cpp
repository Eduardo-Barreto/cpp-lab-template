#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "helpers/subprocess.hpp"

TEST(ContagemUmADez, ImprimeNumeros) {
    auto result = run("contagem-um-a-dez");
    EXPECT_EQ(result.exit_code, 0);

    std::istringstream stream(result.stdout_output);
    std::string        line;
    int                count = 0;

    while (std::getline(stream, line)) {
        if (!line.empty()) {
            count++;
        }
    }

    EXPECT_GE(count, 10);
}

TEST(ContagemUmADez, ContemPrimeiroEUltimo) {
    auto result = run("contagem-um-a-dez");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("1"), std::string::npos);
    EXPECT_NE(result.stdout_output.find("10"), std::string::npos);
}
