#pragma once

#include <rgpu/d3d12/D3D12Buffer.hpp>
#include <rgpu/d3d12/D3D12Texture.hpp>
#include <rgpu/d3d12/D3D12SwapChain.hpp>
#include <rgpu/d3d12/D3D12CommandQueue.hpp>

namespace rgpu {

class GPUDevice final {
public:
    GPUBuffer CreateBuffer(BufferDescriptor descriptor) const noexcept;
    GPUSwapChain CreateSwapChain(GPUSwapChainDescriptor descriptor) const noexcept;
    GPUTexture CreateTexture(GPUTextureDescriptor descriptor) const noexcept;
private:
    friend class GPUAdapter;
    GPUDevice(IDXGIFactory6* factory, IDXGIAdapter1* adapter, ID3D12Device5* device) noexcept;
private:
    IDXGIFactory6* Factory;
    IDXGIAdapter1* Adapter;
    Microsoft::WRL::ComPtr<ID3D12Device5> Device;
public:
    GPUCommandQueue BlitQueue;
    GPUCommandQueue ComputeQueue;
    GPUCommandQueue GraphicsQueue;
};

} // namespace rgpu