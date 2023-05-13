#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUCommandAllocatorImpl {
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CommandAllocator;
};

} // namespace rgpu::internal