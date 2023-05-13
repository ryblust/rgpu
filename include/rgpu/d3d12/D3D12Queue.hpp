#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUQueueImpl {
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> Queue;
};

} // namespace rgpu::internal