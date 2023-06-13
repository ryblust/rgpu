#pragma once

#include <rgpu/rgpu_common.hpp>

#include <dxgi1_6.h>
#include <d3d12.h>
#include <wrl/client.h>

namespace rgpu {

// class BufferView final {
//     friend class Buffer;
//     BufferView(BufferViewDescriptor descriptor, ID3D12Device5* device) noexcept;

//     D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle;
//     D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle;
//     Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DescriptorHeap;
// };

class Buffer final {
public:
    void* Map(std::uint32_t offset, std::uint32_t length) const noexcept;
    void Unmap() const noexcept;

    Buffer() noexcept = default;
    Buffer(Buffer&&) noexcept = default;
    Buffer& operator=(Buffer&&) noexcept = default;
private:
    friend class Device;
    Buffer(ID3D12Resource* resource) noexcept : D3dResource(resource) {}

    Microsoft::WRL::ComPtr<ID3D12Resource> D3dResource;
};

class Texture final {
public:
    // TextureView CreateTextureView(TextureViewDescriptor descriptor) const noexcept;

    Texture() noexcept = default;
    Texture(Texture&&) noexcept = default;
    Texture& operator=(Texture&&) noexcept = default;
private:
    friend class Device;
    Texture(ID3D12Resource* resource) noexcept : D3dResource(resource) {}

    Microsoft::WRL::ComPtr<ID3D12Resource> D3dResource;
};

class CommandQueue final {
public:
    // CommandBuffer CreateCommandBuffer() const noexcept;

    CommandQueue() noexcept = default;
    CommandQueue(CommandQueue&&) noexcept = default;
    CommandQueue& operator=(CommandQueue&&) noexcept = default;
private:
    friend class Device;
    friend class Instance;
    friend class SwapChain;
    CommandQueue(ID3D12CommandQueue* queue) noexcept : D3dCommandQueue(queue) {}

    Microsoft::WRL::ComPtr<ID3D12CommandQueue> D3dCommandQueue;
};

class SwapChain final {
public:
    void Present() const noexcept;

    SwapChain() noexcept = default;
    SwapChain(SwapChain&&) noexcept = default;
    SwapChain& operator=(SwapChain&&) noexcept = default;
private:
    friend class Device;
    SwapChain(SwapChainDescriptor descriptor, IDXGIFactory6* factory) noexcept;

    Microsoft::WRL::ComPtr<IDXGISwapChain4> DxgiSwapChain;
    std::uint32_t BackBufferIndex;
    std::uint32_t PresentFlag;
};

class Device final {
public:
    [[nodiscard]] Buffer CreateBuffer(BufferDescriptor descriptor) const noexcept;
    [[nodiscard]] Texture CreateTexture(TextureDescriptor descriptor) const noexcept;
    [[nodiscard]] SwapChain CreateSwapChain(SwapChainDescriptor descriptor) const noexcept;

    Device() noexcept = default;
    Device(Device&&) noexcept = default;
    Device& operator=(Device&&) noexcept = default;
private:
    friend class Instance;
    Device(IDXGIFactory6* factory, ID3D12Device5* device, ID3D12CommandQueue* blit, ID3D12CommandQueue* compute, ID3D12CommandQueue* graphics) noexcept
        : DxgiFactory(factory), D3dDevice(device), BlitQueue(blit), ComputeQueue(compute), GraphicsQueue(graphics) {}

    IDXGIFactory6* DxgiFactory;
    Microsoft::WRL::ComPtr<ID3D12Device5> D3dDevice;
public:
    CommandQueue BlitQueue;
    CommandQueue ComputeQueue;
    CommandQueue GraphicsQueue;
};

class Instance final {
public:
    [[nodiscard]] Device CreateDevice() const noexcept;

    Instance() noexcept = default;
    Instance(InstanceDescriptor descriptor) noexcept;
    Instance(Instance&&) noexcept = default;
    Instance& operator=(Instance&&) noexcept = default;
private:
    Microsoft::WRL::ComPtr<IDXGIFactory6> DxgiFactory;
};

} // namespace rgpu