#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(MediaArray, MediaCorreta) {
    auto result = run("media-array", "10\n20\n30\n40\n50\n60\n70\n80\n90\n100\n");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_NE(result.stdout_output.find("55"), std::string::npos);
}
