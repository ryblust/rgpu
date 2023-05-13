#pragma once

#include <rgpu/common/Adapter.hpp>
#include <rgpu/d3d12/D3D12Instance.hpp>

namespace rgpu {

struct GPUInstanceDescriptor final {
    bool IsEnableDebugLayer;
    bool IsEnableValidation;
};

struct GPUInstance final : internal::GPUInstanceImpl {
    GPUInstance(GPUInstanceDescriptor descriptor) noexcept;
    GPUAdapter CreateAdapter() const noexcept;
};

} // namespace rgpu