#pragma once

#include <rgpu/common/Texture.hpp>

#include <d3d12.h>
#include <wrl/client.h>

namespace rgpu {

class GPUTextureView final {
    friend class GPUTexture;
    GPUTextureView(GPUTextureViewDescriptor descriptor, ID3D12Device5* device) noexcept;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> TextureDescHeap;
};

class GPUTexture final {
public:
    GPUTextureView CreateTextureView(GPUTextureViewDescriptor descriptor) const noexcept;
private:
    friend class GPUDevice;
    friend class GPUSwapChain;
    GPUTexture(GPUTextureDescriptor descriptor, ID3D12Device5* device) noexcept;
private:
    Microsoft::WRL::ComPtr<ID3D12Resource> Texture;
};

} // namespace rgpu