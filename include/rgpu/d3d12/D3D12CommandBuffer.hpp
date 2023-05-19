#pragma once

#include <d3d12.h>
#include <wrl/client.h>

namespace rgpu {

class GPUCommandBuffer final {
    Microsoft::WRL::ComPtr<ID3D12CommandList> CommandList;
};

} // namespace rgpu