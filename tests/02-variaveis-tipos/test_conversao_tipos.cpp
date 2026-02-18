#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ConversaoTipos, ResultadoCorreto) {
    auto result = run("conversao-tipos");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("7.5"), std::string::npos) << "Deve conter 7.5 (soma de 5 + 2.5)";
}
