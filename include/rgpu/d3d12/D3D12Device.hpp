#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUDeviceImpl {
    IDXGIFactory6* Factory;
    IDXGIAdapter1* Adapter;
    Microsoft::WRL::ComPtr<ID3D12Device5> Device;
};

} // namespace rgpu::internal