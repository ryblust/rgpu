#include <rgpu/d3d12/D3D12Buffer.hpp>

namespace rgpu {

static constexpr D3D12_RESOURCE_STATES MapToD3D12BufferState(BufferState state, BufferUsage usage) noexcept
{
    D3D12_RESOURCE_STATES bufferState = D3D12_RESOURCE_STATE_COMMON;

    if (state.State & BufferState::CopyDst)
        bufferState = bufferState | D3D12_RESOURCE_STATE_COPY_DEST;
    if (state.State & BufferState::CopySrc)
        bufferState = bufferState | D3D12_RESOURCE_STATE_COPY_SOURCE;
    if (state.State & BufferState::GenericRead)
        bufferState = bufferState | D3D12_RESOURCE_STATE_GENERIC_READ;

    if (usage.Usage & BufferUsage::IndexBuffer)
        bufferState = bufferState | D3D12_RESOURCE_STATE_INDEX_BUFFER;
    if (usage.Usage & BufferUsage::VertexBuffer)
        bufferState = bufferState | D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
    if (usage.Usage & BufferUsage::UniformBuffer)
        bufferState = bufferState | D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
    if (usage.Usage & BufferUsage::IndirectBuffer)
        bufferState = bufferState | D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
    if (usage.Usage & BufferUsage::ShaderResource)
        bufferState = bufferState | D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE;
    if (usage.Usage & BufferUsage::UnorderedAccess)
        bufferState = bufferState | D3D12_RESOURCE_STATE_UNORDERED_ACCESS;

    return bufferState;
}

GPUBuffer::GPUBuffer(BufferDescriptor descriptor, ID3D12Device5* device) noexcept
{
    const D3D12_HEAP_PROPERTIES heapProps
    {
        .Type = D3D12_HEAP_TYPE(descriptor.MemoryUsage.Usage + 1),
        .CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
        .MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
        .CreationNodeMask = 1,
        .VisibleNodeMask = 1
    };

    D3D12_RESOURCE_FLAGS bufferFlags = D3D12_RESOURCE_FLAG_NONE;

    if (descriptor.Usage.Usage & BufferUsage::UnorderedAccess)
        bufferFlags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
    if (descriptor.MemoryUsage.Usage == GPUMemoryUsage::GpuToCpu)
        bufferFlags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;

    const D3D12_RESOURCE_DESC bufferDesc
    {
        .Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
        .Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
        .Width = descriptor.Size,
        .Height = 1,
        .DepthOrArraySize = 1,
        .MipLevels = 1,
        .Format = DXGI_FORMAT_UNKNOWN,
        .SampleDesc = {1, 0},
        .Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags = D3D12_RESOURCE_FLAG_NONE
    };

    device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE,
        &bufferDesc, MapToD3D12BufferState(descriptor.State, descriptor.Usage),
        nullptr, IID_PPV_ARGS(Buffer.ReleaseAndGetAddressOf()));
}

void* GPUBuffer::Map(std::uint32_t offset, std::uint32_t length) const noexcept
{
    const D3D12_RANGE range{offset, offset + length};
    void* mappedAddress;
    Buffer->Map(0, &range, &mappedAddress);

    return mappedAddress;
}

void GPUBuffer::Unmap() const noexcept { Buffer->Unmap(0, nullptr); }

// GPUBufferView GPUBuffer::CreateBufferView(GPUBufferViewDescriptor descriptor) const noexcept
// {
//     return 
// }

} // namespace rgpu