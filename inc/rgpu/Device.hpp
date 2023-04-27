#pragma once

#include <rgpu/Buffer.hpp>
#include <rgpu/Pipeline.hpp>
#include <rgpu/QuerySet.hpp>
#include <rgpu/Sampler.hpp>
#include <rgpu/ShaderModule.hpp>
#include <rgpu/SwapChain.hpp>

#include <memory>

namespace rgpu {

class GPUDevice final {
public:




private:
    struct GPUDeviceImpl;
    std::unique_ptr<GPUDeviceImpl> Device;
    GPUQueue Queue[3];
};

} // namespace Rage