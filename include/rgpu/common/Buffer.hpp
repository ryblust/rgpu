#pragma once

#include <cstdint>

namespace rgpu {

inline constexpr std::uint8_t BufferStateCommon      = 0x0;
inline constexpr std::uint8_t BufferStateCopyDst     = 0x1;
inline constexpr std::uint8_t BufferStateCopySrc     = 0x2;
inline constexpr std::uint8_t BufferStateGenericRead = 0x4;

inline constexpr std::uint8_t BufferUsageIndex           = 0x01;
inline constexpr std::uint8_t BufferUsageVertex          = 0x02;
inline constexpr std::uint8_t BufferUsageUniform         = 0x04;
inline constexpr std::uint8_t BufferUsageIndirect        = 0x08;
inline constexpr std::uint8_t BufferUsageShaderResource  = 0x10;
inline constexpr std::uint8_t BufferUsageUnorderedAccess = 0x20;

inline constexpr std::uint8_t GpuOnly  = 0;
inline constexpr std::uint8_t CpuToGpu = 1;
inline constexpr std::uint8_t GpuToCpu = 2;

struct BufferDescriptor final {
    std::uint32_t Size;
    std::uint16_t State;
    std::uint8_t Usage;
    std::uint8_t MemoryUsage;
};

inline constexpr std::uint32_t BufferViewUniform         = 0;
inline constexpr std::uint32_t BufferViewShaderResource  = 1;
inline constexpr std::uint32_t BufferViewUnorderedAccess = 2;

struct BufferViewDescriptor final {
    std::uint32_t Count;
    std::uint32_t Offset;
    std::uint32_t Stride;
    std::uint32_t Type;
};

} // namespace rgpu