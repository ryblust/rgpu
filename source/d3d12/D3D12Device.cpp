#include <rgpu/d3d12/D3D12Device.hpp>

namespace rgpu {

GPUDevice::GPUDevice(IDXGIFactory6* factory, IDXGIAdapter1* adapter, ID3D12Device5* device) noexcept
    : Factory{factory}
    , Adapter{adapter}
    , Device{device}
    , BlitQueue{QueueTypeBlit, device}
    , ComputeQueue{QueueTypeCompute, device}
    , GraphicsQueue{QueueTypeGraphics, device}
{
}

GPUBuffer GPUDevice::CreateBuffer(BufferDescriptor descriptor) const noexcept
{
    return {descriptor, Device.Get()};
}

GPUTexture GPUDevice::CreateTexture(GPUTextureDescriptor descriptor) const noexcept
{
    return {descriptor, Device.Get()};
}

GPUSwapChain GPUDevice::CreateSwapChain(GPUSwapChainDescriptor descriptor) const noexcept
{
    return {descriptor, Factory};
}

} // namespace rgpu