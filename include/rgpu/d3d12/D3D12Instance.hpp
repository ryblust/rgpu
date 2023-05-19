#pragma once

#include <rgpu/common/Instance.hpp>
#include <rgpu/d3d12/D3D12Adapter.hpp>

namespace rgpu {

class GPUInstance final {
public:
    GPUInstance(GPUInstanceDescriptor descriptor) noexcept;
    GPUAdapter CreateAdapter() const noexcept;
private:
    Microsoft::WRL::ComPtr<IDXGIFactory6> Factory;
};

} // namespace rgpu