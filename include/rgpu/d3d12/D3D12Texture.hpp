#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUTextureViewImpl {};

struct GPUTextureImpl {
    Microsoft::WRL::ComPtr<ID3D12Resource> Texture;
};

} // namespace rgpu::internal