#include "helpers/subprocess.hpp"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <sys/wait.h>
#include <unistd.h>

static std::string find_binary(const std::string& name) {
    const char* env_dir = std::getenv("BINARY_DIR");
    if (env_dir) {
        return std::string(env_dir) + "/" + name;
    }
#ifdef BINARY_DIR
    return std::string(BINARY_DIR) + "/" + name;
#else
    return "./" + name;
#endif
}

ProcessResult run(const std::string& binary_name, const std::string& stdin_input) {
    std::string binary_path = find_binary(binary_name);

    int stdin_pipe[2];
    int stdout_pipe[2];
    int stderr_pipe[2];

    if (pipe(stdin_pipe) != 0 || pipe(stdout_pipe) != 0 || pipe(stderr_pipe) != 0) {
        throw std::runtime_error("pipe() failed");
    }

    pid_t pid = fork();
    if (pid < 0) {
        throw std::runtime_error("fork() failed");
    }

    if (pid == 0) {
        close(stdin_pipe[1]);
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);

        dup2(stdin_pipe[0], STDIN_FILENO);
        dup2(stdout_pipe[1], STDOUT_FILENO);
        dup2(stderr_pipe[1], STDERR_FILENO);

        close(stdin_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);

        execl(binary_path.c_str(), binary_path.c_str(), nullptr);
        _exit(127);
    }

    close(stdin_pipe[0]);
    close(stdout_pipe[1]);
    close(stderr_pipe[1]);

    if (!stdin_input.empty()) {
        write(stdin_pipe[1], stdin_input.data(), stdin_input.size());
    }
    close(stdin_pipe[1]);

    ProcessResult result;
    std::array<char, 4096> buffer{};
    ssize_t bytes_read;

    while ((bytes_read = read(stdout_pipe[0], buffer.data(), buffer.size())) > 0) {
        result.stdout_output.append(buffer.data(), static_cast<size_t>(bytes_read));
    }
    close(stdout_pipe[0]);

    while ((bytes_read = read(stderr_pipe[0], buffer.data(), buffer.size())) > 0) {
        result.stderr_output.append(buffer.data(), static_cast<size_t>(bytes_read));
    }
    close(stderr_pipe[0]);

    int status = 0;
    waitpid(pid, &status, 0);
    result.exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

    return result;
}
