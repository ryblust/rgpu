#include <rgpu/common/Instance.hpp>

namespace rgpu {

GPUInstance::GPUInstance(GPUInstanceDescriptor descriptor) noexcept
{
    UINT dxgiFactoryFlag = 0;

    if (descriptor.IsEnableDebugLayer) {
        dxgiFactoryFlag = DXGI_CREATE_FACTORY_DEBUG;

        ID3D12Debug1* debugger;
        D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));
        debugger->EnableDebugLayer();

        if (descriptor.IsEnableValidation)
            debugger->SetEnableGPUBasedValidation(TRUE);

        debugger->Release();
    }

    CreateDXGIFactory2(dxgiFactoryFlag, IID_PPV_ARGS(Factory.ReleaseAndGetAddressOf()));
}

GPUAdapter GPUInstance::CreateAdapter() const noexcept
{
    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
    Factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(adapter.ReleaseAndGetAddressOf()));

    return {Factory.Get(), adapter.Get()};
}

} // namespace rgpu