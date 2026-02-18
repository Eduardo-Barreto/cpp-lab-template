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

TEST(BuscaElemento, Encontrado) {
    auto result = run("busca-elemento", "5\n10\n15\n20\n25\n30\n35\n40\n45\n50\n25\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("4"), std::string::npos);
}

TEST(BuscaElemento, NaoEncontrado) {
    auto result = run("busca-elemento", "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n99\n");
    EXPECT_EQ(result.exit_code, 0);
    auto output = toLower(result.stdout_output);
    EXPECT_TRUE(output.find("encontrad") != std::string::npos || output.find("not found") != std::string::npos);
}
