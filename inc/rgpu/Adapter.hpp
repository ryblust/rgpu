#pragma once
#include <rgpu/Device.hpp>

namespace rgpu {

class GPUAdapter final {
public:
    GPUDevice CreateDevice() const noexcept;



private:
    struct GPUAdapterImpl;
    std::unique_ptr<GPUAdapterImpl> Adapter;
};

} // namespace Rage