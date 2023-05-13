#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUAdapterImpl {
    IDXGIFactory6* Factory;
    Microsoft::WRL::ComPtr<IDXGIAdapter1> Adapter;
};

} // namespace rgpu::internal