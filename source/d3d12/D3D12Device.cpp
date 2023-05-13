#include <rgpu/common/Device.hpp>

namespace rgpu {

static constexpr D3D12_HEAP_TYPE MapToD3D12Heap[]
{
    D3D12_HEAP_TYPE_DEFAULT,
    D3D12_HEAP_TYPE_UPLOAD,
    D3D12_HEAP_TYPE_READBACK
};

static constexpr D3D12_RESOURCE_STATES MapToD3D12ResourceState(GPUBufferState) noexcept
{
    return D3D12_RESOURCE_STATE_COMMON;
};

static constexpr D3D12_RESOURCE_FLAGS MapTpD3D12ResourceFlag[]
{
    D3D12_RESOURCE_FLAG_NONE
};

GPUBuffer GPUDevice::CreateBuffer(GPUBufferDescriptor descriptor) const noexcept
{
    const D3D12_HEAP_PROPERTIES heapProps
    {
        .Type = MapToD3D12Heap[descriptor.StorageMode],
        .CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE,
        .MemoryPoolPreference = D3D12_MEMORY_POOL_L0,
        .CreationNodeMask = 0,
        .VisibleNodeMask = 0
    };

    const D3D12_RESOURCE_DESC bufferDesc
    {
        .Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
        .Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
        .Width = descriptor.Size,
        .Height = 0,
        .DepthOrArraySize = 1,
        .MipLevels = 1,
        .Format = DXGI_FORMAT_UNKNOWN,
        .SampleDesc = {1, 0},
        .Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags = D3D12_RESOURCE_FLAG_NONE
    };

    Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
    Device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc, MapToD3D12ResourceState(descriptor.State), nullptr, IID_PPV_ARGS(buffer.ReleaseAndGetAddressOf()));

    return {buffer.Get()};
}

GPUTexture GPUDevice::CreateTexture([[maybe_unused]] GPUTextureDescriptor descriptor) const noexcept
{
    return {nullptr};
}

GPUSwapChain GPUDevice::CreateSwapChain([[maybe_unused]] GPUSwapChainDescriptor descriptor) const noexcept
{
    return {nullptr};
}

} // namespace rgpu