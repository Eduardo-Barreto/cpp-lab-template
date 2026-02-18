#include <gtest/gtest.h>

#include "helpers/subprocess.hpp"

TEST(OlaMundo, ImprimeHelloWorld) {
    auto result = run("ola-mundo");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_EQ(result.stdout_output, "Hello World!\n");
}
