#include <rgpu/rgpu_d3d12.hpp>

namespace rgpu {

Instance::Instance(InstanceDescriptor descriptor) noexcept
{
    UINT dxgiFactoryFlag = 0;

    if (descriptor.IsEnableDebugLayer)
    {
        dxgiFactoryFlag = DXGI_CREATE_FACTORY_DEBUG;

        ID3D12Debug1* debugger;
        D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));
        debugger->EnableDebugLayer();

        if (descriptor.IsEnableValidation)
            debugger->SetEnableGPUBasedValidation(TRUE);

        debugger->Release();
    }

    CreateDXGIFactory2(dxgiFactoryFlag, IID_PPV_ARGS(DxgiFactory.ReleaseAndGetAddressOf()));
}

Device Instance::CreateDevice() const noexcept
{
    static constexpr D3D12_COMMAND_QUEUE_DESC blitQueueDesc
    {
        .Type = D3D12_COMMAND_LIST_TYPE_COPY,
        .Priority = 0,
        .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
        .NodeMask = 1
    };

    static constexpr D3D12_COMMAND_QUEUE_DESC computeQueueDesc
    {
        .Type = D3D12_COMMAND_LIST_TYPE_COMPUTE,
        .Priority = 0,
        .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
        .NodeMask = 1
    };

    static constexpr D3D12_COMMAND_QUEUE_DESC graphicsQueueDesc
    {
        .Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
        .Priority = 0,
        .Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
        .NodeMask = 1
    };

    Microsoft::WRL::ComPtr<IDXGIAdapter1> dxgiAdapter;
    Microsoft::WRL::ComPtr<ID3D12Device5> d3d12Device;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> blitQueue;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> computeQueue;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> graphicsQueue;

    DxgiFactory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(dxgiAdapter.ReleaseAndGetAddressOf()));
    D3D12CreateDevice(dxgiAdapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(d3d12Device.ReleaseAndGetAddressOf()));

    d3d12Device->CreateCommandQueue(&blitQueueDesc, IID_PPV_ARGS(blitQueue.ReleaseAndGetAddressOf()));
    d3d12Device->CreateCommandQueue(&computeQueueDesc, IID_PPV_ARGS(computeQueue.ReleaseAndGetAddressOf()));
    d3d12Device->CreateCommandQueue(&graphicsQueueDesc, IID_PPV_ARGS(graphicsQueue.ReleaseAndGetAddressOf()));

    return {DxgiFactory.Get(), d3d12Device.Get(), blitQueue.Get(), computeQueue.Get(), graphicsQueue.Get()};
}

Buffer Device::CreateBuffer(BufferDescriptor descriptor) const noexcept
{
    // const auto d3d12HeapType = static_cast<std::underlying_type_t<D3D12_HEAP_TYPE>>(descriptor.MemoryUsage) + 1;

    const D3D12_HEAP_PROPERTIES heapProps
    {
        // .Type = static_cast<D3D12_HEAP_TYPE>(d3d12HeapType),
        .CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
        .MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
        .CreationNodeMask = 1,
        .VisibleNodeMask = 1
    };

    D3D12_RESOURCE_FLAGS bufferFlags = D3D12_RESOURCE_FLAG_NONE;

    if (descriptor.Usage & BufferUsage::UnorderedAccess)
        bufferFlags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    if (descriptor.MemoryUsage == MemoryUsage::GpuToCpu)
        bufferFlags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;

    const D3D12_RESOURCE_DESC bufferDesc
    {
        .Dimension = D3D12_RESOURCE_DIMENSION_BUFFER,
        .Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
        .Width = descriptor.Size,
        .Height = 1,
        .DepthOrArraySize = 1,
        .MipLevels = 1,
        .Format = DXGI_FORMAT_UNKNOWN,
        .SampleDesc = {1, 0},
        .Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
        .Flags = bufferFlags
    };

    static constexpr auto bufferStateMaker = [](BufferState state, BufferUsage usage) noexcept
    {
        D3D12_RESOURCE_STATES bufstate = D3D12_RESOURCE_STATE_COMMON;

        if (state & BufferState::CopyDst)
            bufstate = bufstate | D3D12_RESOURCE_STATE_COPY_DEST;
        if (state & BufferState::CopySrc)
            bufstate = bufstate | D3D12_RESOURCE_STATE_COPY_SOURCE;
        if (state & BufferState::GenericRead)
            bufstate = bufstate | D3D12_RESOURCE_STATE_GENERIC_READ;

        if (usage & BufferUsage::Index)
            bufstate = bufstate | D3D12_RESOURCE_STATE_INDEX_BUFFER;
        if (usage & BufferUsage::Vertex)
            bufstate = bufstate | D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        if (usage & BufferUsage::Uniform)
            bufstate = bufstate | D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
        if (usage & BufferUsage::Indirect)
            bufstate = bufstate | D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
        if (usage & BufferUsage::ShaderResource)
            bufstate = bufstate | D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE;
        if (usage & BufferUsage::UnorderedAccess)
            bufstate = bufstate | D3D12_RESOURCE_STATE_UNORDERED_ACCESS;

        return bufstate;
    };

    const auto bufferState = bufferStateMaker(descriptor.State, descriptor.Usage);

    Microsoft::WRL::ComPtr<ID3D12Resource> resource;
    D3dDevice->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc, bufferState, nullptr, IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));

    return resource.Get();
}

SwapChain::SwapChain(SwapChainDescriptor descriptor, IDXGIFactory6* factory) noexcept
{
    static constexpr DXGI_FORMAT formater[]
    {
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_FORMAT_R10G10B10A2_UNORM
    };

    BOOL isAllowTearing = FALSE;
    UINT swapchainFlags = 0;

    factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &isAllowTearing, sizeof(BOOL));
    swapchainFlags |= isAllowTearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

    const DXGI_SWAP_CHAIN_DESC1 swapchainDesc
    {
        .Width = descriptor.Width,
        .Height = descriptor.Height,
        .Format = formater[static_cast<std::uint64_t>(descriptor.Format)],
        .Stereo = FALSE,
        .SampleDesc = {1, 0},
        .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount = descriptor.BackBufferCount,
        .Scaling = DXGI_SCALING_STRETCH,
        .SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
        .AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
        .Flags = swapchainFlags
    };

    IDXGISwapChain1* swapchain;
    factory->CreateSwapChainForHwnd(descriptor.PresentQueue.D3dCommandQueue.Get(), static_cast<HWND>(descriptor.Surface), &swapchainDesc, nullptr, nullptr, &swapchain);

    swapchain->QueryInterface(DxgiSwapChain.ReleaseAndGetAddressOf());
    BackBufferIndex = DxgiSwapChain->GetCurrentBackBufferIndex();
    PresentFlag |= DXGI_PRESENT_ALLOW_TEARING;
}

Texture Device::CreateTexture(TextureDescriptor descriptor) const noexcept
{
    static constexpr D3D12_HEAP_TYPE mapper[]
    {
        D3D12_HEAP_TYPE_DEFAULT,
        D3D12_HEAP_TYPE_UPLOAD,
        D3D12_HEAP_TYPE_READBACK
    };

    static constexpr D3D12_RESOURCE_DIMENSION dimension[]
    {
        D3D12_RESOURCE_DIMENSION_TEXTURE2D,
        D3D12_RESOURCE_DIMENSION_TEXTURE3D
    };

    const D3D12_HEAP_PROPERTIES heapProps
    {
        .Type = mapper[static_cast<std::uint64_t>(descriptor.MemoryUsage)],
        .CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE,
        .MemoryPoolPreference = D3D12_MEMORY_POOL_L0,
        .CreationNodeMask = 1,
        .VisibleNodeMask = 1
    };

    const D3D12_RESOURCE_DESC textureDesc
    {
        .Dimension = dimension[static_cast<std::uint64_t>(descriptor.Dimension)],
        .Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT,
        .Width = descriptor.Width,
        .Height = descriptor.Height,
        .DepthOrArraySize = descriptor.DepthOrArraySize,
        .MipLevels = descriptor.MipCount,
        .Format = DXGI_FORMAT_UNKNOWN,
        .SampleDesc = {1, 0},
        .Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN,
        .Flags = D3D12_RESOURCE_FLAG_NONE
    };

    Microsoft::WRL::ComPtr<ID3D12Resource> resource;
    D3dDevice->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &textureDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));

    return resource.Get();
}

void* Buffer::Map(std::uint32_t offset, std::uint32_t length) const noexcept
{
    const D3D12_RANGE range{offset, offset + length};
    void* mappedAddress;
    D3dResource->Map(0, &range, &mappedAddress);

    return mappedAddress;
}

void Buffer::Unmap() const noexcept
{
    D3dResource->Unmap(0, nullptr);
}

void SwapChain::Present() const noexcept
{
    // Not implemented
}

} // namespace rgpu