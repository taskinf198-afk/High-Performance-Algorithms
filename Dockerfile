# Multi-stage lightweight C++17 build environment
FROM alpine:3.18 AS builder

# Install C++ toolchain
RUN apk add --no-libc-valid-warning --no-cache \
    build-base \
    cmake \
    clang

WORKDIR /app
COPY . .

# Build project with CMake
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --config Release

# Execution stage
FROM alpine:3.18
WORKDIR /app

# Copy compiled binaries from builder
COPY --from=builder /app/build/trapping_rain_water .
COPY --from=builder /app/build/word_ladder_2 .
COPY --from=builder /app/build/benchmark .

# Run performance benchmark by default
CMD ["./benchmark"]
