#pragma once

#include <rgpu/common/SwapChain.hpp>
#include <rgpu/d3d12/D3D12CommandQueue.hpp>
#include <rgpu/d3d12/D3D12Texture.hpp>

#include <dxgi1_6.h>

namespace rgpu {

class GPUSwapChain final {
public:
    GPUTexture& GetSwapChainSurface() const noexcept;
    void Present() const noexcept; // Todo: Implement this function
private:
    friend class GPUDevice;
    GPUSwapChain(GPUSwapChainDescriptor descriptor, IDXGIFactory6* factory) noexcept;
    GPUSwapChain(const GPUSwapChain& swapchain) = delete;
    GPUSwapChain& operator=(GPUSwapChain&) = delete;
private:
    GPUTexture* RenderTargets; // Todo: Consider a better name
    std::uint32_t PresentFlag; // Todo: Consider whether swapchain should contain it
    std::uint32_t BackBufferIndex;
    Microsoft::WRL::ComPtr<IDXGISwapChain4> SwapChain;
};

} // namespace rgpu