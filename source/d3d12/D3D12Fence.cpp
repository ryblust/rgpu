#include <rgpu/d3d12/D3D12Fence.hpp>

namespace rgpu {

GPUFence::GPUFence(ID3D12Device5* device) noexcept
{
    device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(Fence.ReleaseAndGetAddressOf()));
}

} // namespace rgpu