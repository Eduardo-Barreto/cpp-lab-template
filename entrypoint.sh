#!/bin/bash
set -e

if [ ! -f build/build.ninja ]; then
    cmake --preset dev
fi

exec "$@"
