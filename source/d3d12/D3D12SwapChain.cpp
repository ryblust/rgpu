#include <rgpu/d3d12/D3D12SwapChain.hpp>
#include <rgpu/d3d12/D3D12Texture.hpp>
#include <rgpu/d3d12/D3D12CommandQueue.hpp>

#include <cstdlib> // for std::malloc

namespace rgpu {

static constexpr DXGI_FORMAT MapToDXGISwapChainFormat[]
{
    DXGI_FORMAT_R8G8B8A8_UNORM,
    DXGI_FORMAT_R10G10B10A2_UNORM
};

GPUSwapChain::GPUSwapChain(GPUSwapChainDescriptor descriptor, IDXGIFactory6* factory) noexcept
    : RenderTargets(static_cast<GPUTexture*>(std::malloc(sizeof(GPUTexture) * descriptor.BackBufferCount)))
{
    BOOL isAllowTearing = FALSE;
    UINT swapchainFlags = 0;

    factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &isAllowTearing, sizeof(BOOL));
    swapchainFlags |= isAllowTearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

    const DXGI_SWAP_CHAIN_DESC1 swapchainDesc
    {
        .Width = descriptor.Width,
        .Height = descriptor.Height,
        .Format = MapToDXGISwapChainFormat[descriptor.Format],
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
    factory->CreateSwapChainForHwnd(descriptor.PresentQueue.CommandQueue.Get(), reinterpret_cast<HWND>(descriptor.Surface), &swapchainDesc, nullptr, nullptr, &swapchain);

    swapchain->QueryInterface(SwapChain.ReleaseAndGetAddressOf());
    // PresentFlag |= DXGI_PRESENT_ALLOW_TEARING;
    BackBufferIndex = SwapChain->GetCurrentBackBufferIndex();
}

} // namespace rgpu