#include "helpers/subprocess.hpp"
#include "helpers/pipe.hpp"

#include <array>
#include <cerrno>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

#include <poll.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

std::filesystem::path find_binary(const std::string& name) {
    const char* env_dir = std::getenv("BINARY_DIR");
    if (env_dir != nullptr) {
        return std::filesystem::path(env_dir) / name;
    }
#ifdef BINARY_DIR
    return std::filesystem::path(BINARY_DIR) / name;
#else
    return std::filesystem::path(".") / name;
#endif
}

void close_poll_fd(std::array<struct pollfd, 3>& fds, int index, int& open_fds) {
    ::close(fds[index].fd);
    fds[index].fd = -1;
    --open_fds;
}

void poll_io(int stdin_fd, const std::string& stdin_input, int stdout_fd, int stderr_fd, ProcessResult& result) {
    constexpr int MAX_FDS = 3;

    std::array<struct pollfd, MAX_FDS> fds{};
    fds[0] = {.fd = stdin_fd, .events = POLLOUT, .revents = 0};
    fds[1] = {.fd = stdout_fd, .events = POLLIN, .revents = 0};
    fds[2] = {.fd = stderr_fd, .events = POLLIN, .revents = 0};

    size_t                 stdin_offset = 0;
    int                    open_fds = MAX_FDS;
    std::array<char, 4096> buffer{};

    if (stdin_input.empty()) {
        close_poll_fd(fds, 0, open_fds);
    }

    while (open_fds > 0) {
        const int ret = poll(fds.data(), MAX_FDS, -1);
        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            throw std::runtime_error("poll() failed");
        }

        if (fds[0].fd >= 0 && (fds[0].revents & (POLLOUT | POLLERR | POLLHUP)) != 0) {
            const size_t  remaining = stdin_input.size() - stdin_offset;
            const ssize_t written = write(fds[0].fd, stdin_input.data() + stdin_offset, remaining);
            if (written > 0) {
                stdin_offset += static_cast<size_t>(written);
                if (stdin_offset >= stdin_input.size()) {
                    close_poll_fd(fds, 0, open_fds);
                }
            } else if (written < 0 && errno != EINTR) {
                close_poll_fd(fds, 0, open_fds);
            }
        }

        for (int idx = 1; idx <= 2; ++idx) {
            if (fds[idx].fd < 0 || (fds[idx].revents & (POLLIN | POLLHUP | POLLERR)) == 0) {
                continue;
            }

            const ssize_t bytes_read = read(fds[idx].fd, buffer.data(), buffer.size());
            if (bytes_read > 0) {
                auto& target = (idx == 1) ? result.stdout_output : result.stderr_output;
                target.append(buffer.data(), static_cast<size_t>(bytes_read));
            } else if (bytes_read == 0 || errno != EINTR) {
                close_poll_fd(fds, idx, open_fds);
            }
        }
    }
}

}  // namespace

ProcessResult run(const std::string& binary_name, const std::string& stdin_input) {
    const auto binary_path = find_binary(binary_name).string();

    auto stdin_pipe = create_pipe();
    auto stdout_pipe = create_pipe();
    auto stderr_pipe = create_pipe();

    const pid_t pid = fork();
    if (pid < 0) {
        throw std::runtime_error("fork() failed");
    }

    if (pid == 0) {
        dup2(stdin_pipe.read_end.get(), STDIN_FILENO);
        dup2(stdout_pipe.write_end.get(), STDOUT_FILENO);
        dup2(stderr_pipe.write_end.get(), STDERR_FILENO);

        stdin_pipe.read_end.close();
        stdin_pipe.write_end.close();
        stdout_pipe.read_end.close();
        stdout_pipe.write_end.close();
        stderr_pipe.read_end.close();
        stderr_pipe.write_end.close();

        execl(binary_path.c_str(), binary_path.c_str(), nullptr);
        _exit(127);
    }

    stdin_pipe.read_end.close();
    stdout_pipe.write_end.close();
    stderr_pipe.write_end.close();

    ProcessResult result;
    poll_io(
        stdin_pipe.write_end.release(), stdin_input, stdout_pipe.read_end.release(), stderr_pipe.read_end.release(),
        result
    );

    int status = 0;
    waitpid(pid, &status, 0);
    result.exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

    return result;
}
