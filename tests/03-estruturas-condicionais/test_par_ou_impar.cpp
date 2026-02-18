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

TEST(ParOuImpar, Par) {
    auto result = run("par-ou-impar", "4\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("par"), std::string::npos);
}

TEST(ParOuImpar, Impar) {
    auto result = run("par-ou-impar", "7\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("mpar"), std::string::npos);
}

TEST(ParOuImpar, Zero) {
    auto result = run("par-ou-impar", "0\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_NE(output.find("par"), std::string::npos);
}
