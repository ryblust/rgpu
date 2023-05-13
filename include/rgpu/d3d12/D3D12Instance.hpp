#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUInstanceImpl {
    Microsoft::WRL::ComPtr<IDXGIFactory6> Factory;
};

} // namespace rgpu