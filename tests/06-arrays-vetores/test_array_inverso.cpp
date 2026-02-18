#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(ArrayInverso, OrdemReversa) {
    auto result = run("array-inverso", "1\n2\n3\n4\n5\n");
    EXPECT_EQ(result.exit_code, 0);

    auto& out  = result.stdout_output;
    auto  pos5 = out.find('5');
    auto  pos1 = out.find('1');

    EXPECT_NE(pos5, std::string::npos);
    EXPECT_NE(pos1, std::string::npos);
    EXPECT_LT(pos5, pos1);
}
