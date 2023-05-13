#pragma once

#include <rgpu/d3d12/d3d12.hpp>

namespace rgpu::internal {

struct GPUSwapChainImpl {
    Microsoft::WRL::ComPtr<IDXGISwapChain3> SwapChain;
};

} // namespace rgpu::internal