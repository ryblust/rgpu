#pragma once

#include <cstdint>

namespace rgpu {

struct GPUQueueType final {
    static constexpr std::uint8_t Blit     = 0;
    static constexpr std::uint8_t Compute  = 1;
    static constexpr std::uint8_t Graphics = 2;
    constexpr GPUQueueType(std::uint8_t type) noexcept : Type{type} {}
    std::uint8_t Type;
};

using QueueType = std::uint8_t;
inline constexpr std::uint8_t QueueTypeBlit     = 0;
inline constexpr std::uint8_t QueueTypeCompute  = 1;
inline constexpr std::uint8_t QueueTypeGraphics = 1;

} // namespace rgpu