#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ConcatenaStrings, DuasPalavras) {
    auto result = run("concatena-strings", "hello\nworld\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("hello"), std::string::npos);
    EXPECT_NE(result.stdout_output.find("world"), std::string::npos);
}
