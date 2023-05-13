#pragma once

#include <rgpu/d3d12/D3D12Queue.hpp>
#include <cstdint>

namespace rgpu {

struct GPUQueueType final {
    static constexpr std::uint8_t Blit     = 0;
    static constexpr std::uint8_t Compute  = 1;
    static constexpr std::uint8_t Graphics = 2;

    constexpr GPUQueueType(std::uint8_t type) noexcept : Type{type} {}
    constexpr operator std::uint8_t() const noexcept { return Type; }

    std::uint8_t Type;
};

struct GPUQueue : internal::GPUQueueImpl {
};

} // namespace rgpu