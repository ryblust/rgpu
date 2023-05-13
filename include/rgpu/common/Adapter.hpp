#pragma once

#include <rgpu/common/Device.hpp>
#include <rgpu/d3d12/D3D12Adapter.hpp>

namespace rgpu {

struct GPUAdapterInfo final {
    const std::uint32_t VendorID;
    const std::uint32_t DeviceID;
};

struct GPUAdapter final : internal::GPUAdapterImpl {
    GPUDevice CreateDevice() const noexcept;
    GPUAdapterInfo GetAdapterInfo() const noexcept;
};

} // namespace rgpu