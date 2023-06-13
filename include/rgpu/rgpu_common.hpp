#pragma once

#include <cstdint>

namespace rgpu {

struct InstanceDescriptor final {
    bool IsEnableDebugLayer;
    bool IsEnableValidation;
};

struct AdapterInfo final {
    const std::uint32_t VendorID;
    const std::uint32_t DeviceID;
};

enum class MemoryUsage : std::uint16_t {
    GpuOnly,
    CpuToGpu,
    GpuToCpu
};

enum class BufferState : std::uint8_t {
    Common      = 0x0,
    CopyDst     = 0x1,
    CopySrc     = 0x2,
    GenericRead = 0x4
};

enum class BufferUsage : std::uint8_t {
    Index           = 0x01,
    Vertex          = 0x02,
    Uniform         = 0x04,
    Indirect        = 0x08,
    ShaderResource  = 0x10,
    UnorderedAccess = 0x20
};

constexpr bool operator&(BufferState a, BufferState b) noexcept { return static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b); }
constexpr bool operator&(BufferUsage a, BufferUsage b) noexcept { return static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b); }

struct BufferDescriptor final {
    std::uint32_t Size;
    BufferState State;
    BufferUsage Usage;
    MemoryUsage MemoryUsage;
};

enum class BufferViewType : std::uint32_t {
    Uniform,
    ShaderResource,
    UnorderedAccess
};

struct BufferViewDescriptor final {
    std::uint32_t Count;
    std::uint32_t Offset;
    std::uint32_t Stride;
    BufferViewType ViewType;
};

enum class TextureState : std::uint16_t {
    Common          = 0x000,
    Present         = 0x001,
    GenericRead     = 0x002,
    CopyDst         = 0x004,
    CopySrc         = 0x008,
    ResolveDst      = 0x010,
    ResolveSrc      = 0x020,
    DepthRead       = 0x040,
    DepthWrite      = 0x080,
    RenderTarget    = 0x100,
    ShaderResource  = 0x200,
    UnorderedAccess = 0x400
};

enum class TextureUsage : std::uint8_t {
    RenderTarget    = 0x1,
    DepthStencil    = 0x2,
    ShaderResource  = 0x2,
    UnorderedAccess = 0x4
};

enum class PixelFormat : std::uint8_t {
    RGBA8UNorm
};

enum class TextureDimension : std::uint8_t {
    Texture2D,
    Texture3D
};

struct TextureDescriptor final {
    std::uint32_t Width;
    std::uint32_t Height;
    std::uint16_t DepthOrArraySize;
    std::uint8_t MipCount;
    std::uint8_t Samples;
    TextureState State;
    TextureUsage Usage;
    PixelFormat PixelFormat;
    TextureDimension Dimension;
    MemoryUsage MemoryUsage;
};

enum class TextureViewType : std::uint8_t {
    DepthStencil    = 0,
    RenderTarget    = 1,
    ShaderResource  = 1,
    UnorderedAccess = 2
};

struct TextureViewDescriptor final {
    std::uint32_t MipCount;
    std::uint32_t BaseMipLevel;
    std::uint32_t BaseArrayLayer;
    std::uint32_t ArrayLayerCount;
    PixelFormat Format;
    TextureViewType ViewType;
    TextureDimension Dimension;
};

enum class SwapChainFormat : std::uint16_t {
    RGBA8UNorm,
    RGB10A2UNorm
};

class CommandQueue;

struct SwapChainDescriptor final {
    std::uint32_t Width;
    std::uint32_t Height;
    SwapChainFormat Format;
    std::uint32_t BackBufferCount;
    CommandQueue& PresentQueue;
    void* Surface;
};

enum class CommandQueueType : std::uint8_t {
    Blit,
    Compute,
    Graphics
};

enum class LoadAction : std::uint32_t {
    Load,
    Clear
};

enum class StoreAction : std::uint32_t {
    Store,
    Discard
};

class TextureView;

struct ColorAttachmentDescriptor final {
    TextureView* RenderTarget;
    // TextureView* ResolveTarget;
    float ClearValue[4];
    LoadAction LoadAction;
    StoreAction StoreAction;
};

class Texture;

struct TextureBarrier final {
    Texture& texture;
    TextureState before;
    TextureState after;
};

} // namespace rgpu