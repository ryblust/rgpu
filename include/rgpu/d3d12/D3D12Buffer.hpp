#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUBufferViewImpl {
};

struct GPUBufferImpl {
    Microsoft::WRL::ComPtr<ID3D12Resource> Buffer;
};

} // namespace rgpu::internal