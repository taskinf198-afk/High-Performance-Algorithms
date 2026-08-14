#ifndef ARENA_ALLOCATOR_HPP
#define ARENA_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

// Low-Latency High-Performance Arena Allocator
// Bypasses OS malloc/free overhead for hot-loop algorithmic execution.
class ArenaAllocator {
private:
    std::vector<uint8_t> buffer;
    size_t offset{0};

public:
    explicit ArenaAllocator(size_t capacity) {
        buffer.resize(capacity);
    }

    // O(1) Fast Linear Allocation
    void* allocate(size_t bytes, size_t alignment = alignof(std::max_align_t)) {
        size_t current_ptr = reinterpret_cast<size_t>(buffer.data() + offset);
        size_t padding = (alignment - (current_ptr % alignment)) % alignment;

        if (offset + padding + bytes > buffer.size()) {
            std::cerr << "[Arena Exception] Out of pre-allocated memory!\n";
            return nullptr;
        }

        offset += padding;
        void* ptr = buffer.data() + offset;
        offset += bytes;
        return ptr;
    }

    // O(1) Instant Reset for Next Iteration/Test Case
    void reset() noexcept {
        offset = 0;
    }

    [[nodiscard]] size_t get_used_bytes() const noexcept { return offset; }
    [[nodiscard]] size_t get_capacity() const noexcept { return buffer.size(); }
};

#endif // ARENA_ALLOCATOR_HPP
