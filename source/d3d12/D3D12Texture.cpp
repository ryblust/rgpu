#include <rgpu/d3d12/D3D12Texture.hpp>

namespace rgpu {

GPUTexture::GPUTexture(GPUTextureDescriptor descriptor, ID3D12Device5* device) noexcept
{
    const D3D12_HEAP_PROPERTIES heapProps
    {
        .Type = D3D12_HEAP_TYPE(descriptor.MemoryUsage.Mode),
        .CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE,
        .MemoryPoolPreference = D3D12_MEMORY_POOL_L0,
        .CreationNodeMask = 1,
        .VisibleNodeMask = 1
    };

    const D3D12_RESOURCE_DESC textureDesc
    {
        .Dimension = D3D12_RESOURCE_DIMENSION(descriptor.Dimension + 3),
        .Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
        .Width = descriptor.Width,
        .Height = descriptor.Height,
        .DepthOrArraySize = descriptor.DepthOrArraySize,
        .MipLevels = descriptor.Mips,
        .Format = DXGI_FORMAT_UNKNOWN,
        .SampleDesc = {1, 0},
        .Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags = D3D12_RESOURCE_FLAG_NONE
    };

    device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(Texture.ReleaseAndGetAddressOf()));
}

} // namespace rgpu