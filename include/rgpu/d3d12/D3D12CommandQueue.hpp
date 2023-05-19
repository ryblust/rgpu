#pragma once

#include <rgpu/common/CommandQueue.hpp>

#include <d3d12.h>
#include <wrl/client.h>

namespace rgpu {

class GPUCommandQueue final {
private:
    GPUCommandQueue(GPUQueueType type, ID3D12Device5* device) noexcept;
private:
    friend class GPUDevice;
    friend class GPUSwapChain;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> CommandQueue;
};

} // namespace rgpu