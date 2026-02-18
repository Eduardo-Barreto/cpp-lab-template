#pragma once

#include <unistd.h>

class FileDescriptor {
public:
    explicit FileDescriptor(int file_desc = -1) : fd_(file_desc) { }

    ~FileDescriptor() { close(); }

    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    FileDescriptor(FileDescriptor&& other) noexcept : fd_(other.fd_) { other.fd_ = -1; }

    FileDescriptor& operator=(FileDescriptor&& other) noexcept {
        if (this != &other) {
            close();
            fd_ = other.fd_;
            other.fd_ = -1;
        }
        return *this;
    }

    [[nodiscard]] int get() const { return fd_; }

    int release() {
        const int file_desc = fd_;
        fd_ = -1;
        return file_desc;
    }

    void close() {
        if (fd_ >= 0) {
            ::close(fd_);
            fd_ = -1;
        }
    }

private:
    int fd_;
};
