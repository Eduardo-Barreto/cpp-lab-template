#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(MaiorDeTres, PrimeiroMaior) {
    auto result = run("maior-de-tres", "10\n5\n3\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("10"), std::string::npos);
}

TEST(MaiorDeTres, SegundoMaior) {
    auto result = run("maior-de-tres", "2\n9\n4\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("9"), std::string::npos);
}

TEST(MaiorDeTres, TerceiroMaior) {
    auto result = run("maior-de-tres", "1\n3\n7\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("7"), std::string::npos);
}
