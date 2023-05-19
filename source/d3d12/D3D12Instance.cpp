#include <rgpu/d3d12/D3D12Instance.hpp>

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
    return Factory.Get();
}

} // namespace rgpu