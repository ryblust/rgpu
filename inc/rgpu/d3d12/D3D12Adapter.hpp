#pragma once
#include <rgpu/d3d12/D3D12Common.hpp>

namespace rgpu {

class GPUAdatper final {
public:
    GPUAdatper() noexcept;

    GPUDevice CreateDevice() const noexcept;
private:
    Microsoft::WRL::ComPtr<IDXGIAdapter1> Adapter;
};

} // namespace rgpu