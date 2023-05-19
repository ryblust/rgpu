#pragma once

#include <rgpu/common/Buffer.hpp>

#include <d3d12.h>
#include <wrl/client.h>

namespace rgpu {

class GPUBufferView {
private:
    friend class GPUBuffer;
    GPUBufferView(BufferViewDescriptor descriptor, ID3D12Device5* device) noexcept;
private:
    D3D12_CPU_DESCRIPTOR_HANDLE CPUHandle;
    D3D12_GPU_DESCRIPTOR_HANDLE GPUHandle;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> BufferDescHeap;
};

class GPUBuffer final {
public:
    GPUBufferView CreateBufferView(BufferViewDescriptor descriptor) const noexcept;
    void* Map(std::uint32_t offset = 0, std::uint32_t length = 0) const noexcept;
    void Unmap() const noexcept;
private:
    friend class GPUDevice;
    GPUBuffer(BufferDescriptor descriptor, ID3D12Device5* device) noexcept;
private:
    Microsoft::WRL::ComPtr<ID3D12Resource> Buffer;
};

} // namespace rgpu