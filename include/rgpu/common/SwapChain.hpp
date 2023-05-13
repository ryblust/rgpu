#pragma once

#include <rgpu/common/Queue.hpp>
#include <rgpu/common/Texture.hpp>
#include <rgpu/d3d12/D3D12SwapChain.hpp>

namespace rgpu {

enum class GPUPresentMode : std::uint16_t {
    Immediately, VSync
};

struct GPUSwapChainFormat final {
    static constexpr std::uint16_t RGBA8UNorm   = 0;
    static constexpr std::uint16_t RGB10A2UNorm = 1;

    GPUSwapChainFormat(std::uint16_t format) noexcept : Format(format) {}
    constexpr operator std::uint16_t() const noexcept { return Format; }

    std::uint16_t Format;
};

struct GPUSwapChainDescriptor final {
    std::uint32_t Width;
    std::uint32_t Height;
    std::uint32_t BackBufferCount;
    GPUPresentMode PresentMode;
    GPUSwapChainFormat Format;
    void* Surface;
    GPUQueue& PresentQueue;
};

struct GPUSwapChain final : internal::GPUSwapChainImpl {
    std::uint32_t GetCurrentFrameIndex() const noexcept;
    GPUTexture& FetchRenderTarget() const noexcept;
};

} // namespace rgpu