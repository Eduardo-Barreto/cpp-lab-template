#pragma once

#include "helpers/file_descriptor.hpp"

#include <stdexcept>

#include <fcntl.h>

struct Pipe {
    FileDescriptor read_end;
    FileDescriptor write_end;
};

inline Pipe create_pipe() {
    int fds[2];
    if (pipe2(fds, O_CLOEXEC) != 0) {
        throw std::runtime_error("pipe2() failed");
    }
    return {FileDescriptor(fds[0]), FileDescriptor(fds[1])};
}
