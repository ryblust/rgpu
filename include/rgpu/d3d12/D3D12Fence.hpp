#pragma once

#include <d3d12.h>
#include <wrl/client.h>

namespace rgpu {

class GPUFence final {
private:
    friend class GPUDevice;
    GPUFence(ID3D12Device5* device) noexcept;
private:
    Microsoft::WRL::ComPtr<ID3D12Fence> Fence;
};

} // namespace rgpu