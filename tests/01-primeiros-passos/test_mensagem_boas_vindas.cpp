#include <gtest/gtest.h>

#include <string>

#include "helpers/subprocess.hpp"

TEST(MensagemBoasVindas, ImprimeComLinhaEmBranco) {
    auto result = run("mensagem-boas-vindas");
    EXPECT_EQ(result.exit_code, 0);
    EXPECT_FALSE(result.stdout_output.empty());
    EXPECT_NE(result.stdout_output.find("\n\n"), std::string::npos)
        << "Deve ter uma linha em branco separando as mensagens";
}
