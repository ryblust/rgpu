#pragma once

#include <rgpu/d3d12/D3D12Buffer.hpp>
#include <cstdint>

namespace rgpu {

enum class GPUBufferState : std::uint16_t {
    Common           = 0x000,
    GenericRead      = 0x001,
    CopyDest         = 0x002,
    CopySource       = 0x004,
    VertexBuffer     = 0x008,
    ConstantBuffer   = 0x010,
    IndexBuffer      = 0x020,
    ShaderResource   = 0x040,
    IndirectArgument = 0x080,
    UnorderedAccess  = 0x100
};

enum class GPUBufferUsage : std::uint8_t {
    Unspecified     = 0x00,
    VertexBuffer    = 0x01,
    UniformBuffer   = 0x02,
    IndexBuffer     = 0x04,
    IndirectBuffer  = 0x08,
    ShaderResource  = 0x10,
    UnorderedAccess = 0x20
};

struct GPUStorageMode final {
    static constexpr std::uint8_t GpuOnly  = 0;
    static constexpr std::uint8_t CpuToGpu = 1;
    static constexpr std::uint8_t GpuToCpu = 2;

    constexpr GPUStorageMode(std::uint8_t mode) noexcept : Mode{mode} {}
    constexpr operator std::uint8_t() const noexcept { return Mode; }

    std::uint8_t Mode;
};

struct GPUBufferDescriptor final {
    std::uint32_t Size;
    GPUBufferState State;
    GPUBufferUsage Usage;
    GPUStorageMode StorageMode;
};

struct GPUBufferViewType final {
    static constexpr std::uint32_t UniformBuffer   = 0;
    static constexpr std::uint32_t ShaderResource  = 1;
    static constexpr std::uint32_t UnorderedAccess = 2;

    constexpr GPUBufferViewType(std::uint32_t type) noexcept : Type{type} {}
    constexpr operator std::uint32_t() const noexcept { return Type; }

    std::uint32_t Type;
};

struct GPUBufferViewDescriptor final {
    std::uint32_t Count;
    std::uint32_t Offset;
    std::uint32_t Stride;
    GPUBufferViewType ViewType;
};

struct GPUBufferView final : internal::GPUBufferViewImpl {
};

struct GPUBuffer final : internal::GPUBufferImpl {
    GPUBufferView CreateBufferView() const noexcept;
};

} // namespace rgpu