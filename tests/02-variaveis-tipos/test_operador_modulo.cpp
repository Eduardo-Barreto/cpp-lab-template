#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "helpers/subprocess.hpp"

TEST(OperadorModulo, ResultadoCorreto) {
    auto result = run("operador-modulo");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());

    auto newlines = std::count(result.stdout_output.begin(), result.stdout_output.end(), '\n');
    EXPECT_GE(newlines, 3) << "Deve imprimir pelo menos tres resultados";
}
