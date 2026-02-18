#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ConversaoTemperatura, CemGraus) {
    auto result = run("conversao-temperatura", "100\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("212"), std::string::npos);
}

TEST(ConversaoTemperatura, ZeroGraus) {
    auto result = run("conversao-temperatura", "0\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("32"), std::string::npos);
}
