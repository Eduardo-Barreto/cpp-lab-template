#pragma once

#include <string>

struct ProcessResult {
    std::string stdout_output;
    std::string stderr_output;
    int         exit_code;
};

ProcessResult run(const std::string& binary_name, const std::string& stdin_input = "");
