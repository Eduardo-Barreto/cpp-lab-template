#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ClasseRetangulo, ImprimeAreaEPerimetro) {
    auto result = run("classe-retangulo");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());
}
