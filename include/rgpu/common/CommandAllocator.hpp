#pragma once

#include <rgpu/d3d12/D3D12CommandAllocator.hpp>

namespace rgpu {

struct GPUCommandAllocator final : internal::GPUCommandAllocatorImpl {};

} // namespace rgpu