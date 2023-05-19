#include <rgpu/d3d12/D3D12CommandQueue.hpp>

namespace rgpu {

static constexpr D3D12_COMMAND_LIST_TYPE MapToD3D12CommandListType[]
{
    D3D12_COMMAND_LIST_TYPE_COPY,
    D3D12_COMMAND_LIST_TYPE_COMPUTE,
    D3D12_COMMAND_LIST_TYPE_DIRECT
};

GPUCommandQueue::GPUCommandQueue(GPUQueueType type, ID3D12Device5* device) noexcept
{
    const D3D12_COMMAND_QUEUE_DESC queueDesc
    {
        .Type = MapToD3D12CommandListType[type.Type],
        .Priority = 0,
        .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
        .NodeMask = 1
    };

    device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(CommandQueue.ReleaseAndGetAddressOf()));
}

} // namespace rgpu