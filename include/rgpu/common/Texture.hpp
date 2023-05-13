#pragma once

#include <rgpu/common/Buffer.hpp>
#include <rgpu/d3d12/D3D12Texture.hpp>

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
    constexpr operator std::uint8_t() const noexcept { return Format; }

    std::uint8_t Format;
};

struct GPUTextureDimension final {
    static constexpr std::uint8_t Texture2D = 0;
    static constexpr std::uint8_t Texture3D = 1;

    constexpr GPUTextureDimension(std::uint8_t dimension) noexcept : Dimension{dimension} {}
    constexpr operator std::uint8_t() const noexcept { return Dimension; }

    std::uint8_t Dimension;
};

struct GPUTextureDescriptor final {
    std::uint32_t Width;
    std::uint32_t Height;
    std::uint16_t DepthOrArraySize;
    std::uint8_t Mips;
    std::uint8_t Samples;
    GPUTextureState State;
    GPUTextureUsage Usage;
    GPUPixelFormat PixelFormat;
    GPUTextureDimension Dimension;
    GPUStorageMode StorageMode;
};

struct GPUTextureViewType final {
};

struct GPUTextureViewDescriptor final {
    std::uint32_t MipCount;
    std::uint32_t BaseMipLevel;
    std::uint32_t BaseArrayLayer;
    std::uint32_t ArrayLayerCount;
    GPUPixelFormat Format;
    GPUTextureViewType ViewType;
    GPUTextureDimension Dimension;
};

struct GPUTextureView : internal::GPUTextureViewImpl {};

struct GPUTexture : internal::GPUTextureImpl {
    GPUTextureView CreateTextureView() const noexcept;
};

} // namespace rgpu