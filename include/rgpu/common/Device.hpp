#pragma once

#include <rgpu/common/SwapChain.hpp>
#include <rgpu/d3d12/D3D12Device.hpp>

namespace rgpu {

struct GPUDevice final : internal::GPUDeviceImpl {
    GPUBuffer CreateBuffer(GPUBufferDescriptor descriptor) const noexcept;
    GPUTexture CreateTexture(GPUTextureDescriptor descriptor) const noexcept;
    GPUSwapChain CreateSwapChain(GPUSwapChainDescriptor descriptor) const noexcept;
};

} // namespace rgpu