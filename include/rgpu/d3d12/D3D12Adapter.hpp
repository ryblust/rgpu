#pragma once

#include <rgpu/common/Adapter.hpp>
#include <rgpu/d3d12/D3D12Device.hpp>

namespace rgpu {

class GPUAdapter final {
public:
    GPUDevice CreateDevice() const noexcept;
    GPUAdapterInfo GetAdapterInfo() const noexcept;
private:
    friend class GPUInstance;
    GPUAdapter(IDXGIFactory6* factory) noexcept;
private:
    IDXGIFactory6* Factory;
    Microsoft::WRL::ComPtr<IDXGIAdapter1> Adapter;
};

} // namespace rgpu