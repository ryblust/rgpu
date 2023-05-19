#pragma once

#include <cstdint>

namespace rgpu {

using SwapChainFormat = std::uint16_t;
inline constexpr std::uint16_t SwapChainFormatRGBA8UNorm   = 0;
inline constexpr std::uint16_t SwapChainFormatRGB10A2UNorm = 1;

class GPUCommandQueue;

struct GPUSwapChainDescriptor final {
    std::uint32_t Width;
    std::uint32_t Height;
    SwapChainFormat Format;
    std::uint32_t BackBufferCount;
    GPUCommandQueue& PresentQueue;
    void* Surface;
};

} // namespace rgpu