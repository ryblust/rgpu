#pragma once

#include <rgpu/Queue.hpp>
#include <rgpu/Texture.hpp>

namespace rgpu {

struct GPUSwapChainDescriptor final {

};

class GPUSwapChain final {
public:
    GPUSwapChain() noexcept;
private:
    struct GPUSwapChainImpl;
    GPUSwapChainImpl* SwapChain;
};

} // namespace rgpu