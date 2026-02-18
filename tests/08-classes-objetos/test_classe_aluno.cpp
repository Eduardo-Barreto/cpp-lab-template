#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ClasseAluno, ExibeBoletins) {
    auto result = run("classe-aluno");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());
}
