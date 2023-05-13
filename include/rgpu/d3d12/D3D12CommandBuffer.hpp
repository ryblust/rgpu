#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUCommandBufferImpl {
    Microsoft::WRL::ComPtr<ID3D12CommandList> CommandList;
};

} // namespace rgpu::internal