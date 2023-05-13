#pragma once

#include <rgpu/d3d12/D3D12Pipeline.hpp>

namespace rgpu {

struct GPUComputePipeline : internal::GPUComputePipelineImpl {};
struct GPURenderPipeline : internal::GPURenderPipelineImpl {};
struct GPUBlitPipeline : internal::GPUBlitPipelineImpl {};

} // namespace rgpu