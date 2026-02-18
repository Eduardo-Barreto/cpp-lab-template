FROM gcc:15

ARG CMAKE_VERSION=4.2.3

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ninja-build \
        clang-format \
        clang-tidy \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL \
        "https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-x86_64.tar.gz" \
    | tar xz -C /usr/local --strip-components=1

WORKDIR /app

COPY entrypoint.sh /usr/local/bin/
ENTRYPOINT ["entrypoint.sh"]
