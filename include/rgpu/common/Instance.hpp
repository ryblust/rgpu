#pragma once

namespace rgpu {

struct GPUInstanceDescriptor final {
    bool IsEnableDebugLayer;
    bool IsEnableValidation;
};

} // namespace rgpu