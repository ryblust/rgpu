#pragma once

#include <rgpu/common/Buffer.hpp>

namespace rgpu {

enum class GPUTextureState : std::uint16_t {
    Common          = 0x000,
    Present         = 0x001,
    GenericRead     = 0x002,
    CopyDest        = 0x004,
    CopySource      = 0x008,
    ResolveDest     = 0x010,
    ResolveSource   = 0x020,
    DepthRead       = 0x040,
    DepthWrite      = 0x080,
    RenderTarget    = 0x100,
    ShaderResource  = 0x200,
    UnorderedAccess = 0x400
};

enum class GPUTextureUsage : std::uint8_t {
    RenderTarget    = 0x1,
    DepthStencil    = 0x2,
    ShaderResource  = 0x2,
    UnorderedAccess = 0x4
};

struct GPUPixelFormat final {
    static constexpr std::uint8_t RGBA8UNORM = 0;
    constexpr GPUPixelFormat(std::uint8_t format) noexcept : Format{format} {}
    std::uint8_t Format;
};

using TextureDimension = std::uint8_t;
inline constexpr std::uint8_t Texture2D = 0;
inline constexpr std::uint8_t Texture3D = 1;

struct GPUTextureDescriptor final {
    std::uint32_t Width;
    std::uint32_t Height;
    std::uint16_t DepthOrArraySize;
    std::uint8_t Mips;
    std::uint8_t Samples;
    GPUTextureState State;
    GPUTextureUsage Usage;
    GPUPixelFormat PixelFormat;
    TextureDimension Dimension;
    GPUMemoryUsage MemoryUsage;
};

struct GPUTextureViewType final {
    static constexpr std::uint8_t DepthStencil    = 0;
    static constexpr std::uint8_t RenderTarget    = 1;
    static constexpr std::uint8_t ShaderResource  = 1;
    static constexpr std::uint8_t UnorderedAccess = 2;
    constexpr GPUTextureViewType(std::uint8_t type) noexcept : Type(type) {}
    std::uint8_t Type;
};

inline constexpr std::uint8_t DepthStencilView    = 0;
inline constexpr std::uint8_t RenderTargetView    = 1;
// inline constexpr std::uint8_t ShaderResourceView  = 1;
// inline constexpr std::uint8_t UnorderedAccessView = 2;

struct GPUTextureViewDescriptor final
{
    std::uint32_t MipCount;
    std::uint32_t BaseMipLevel;
    std::uint32_t BaseArrayLayer;
    std::uint32_t ArrayLayerCount;
    GPUPixelFormat Format;
    GPUTextureViewType ViewType;
    TextureDimension Dimension;
};

} // namespace rgpu