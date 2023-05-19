#include <rgpu/d3d12/D3D12Adapter.hpp>

namespace rgpu {

GPUAdapter::GPUAdapter(IDXGIFactory6* factory) noexcept
{
    factory->EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(Adapter.ReleaseAndGetAddressOf()));
}

GPUDevice GPUAdapter::CreateDevice() const noexcept
{
    Microsoft::WRL::ComPtr<ID3D12Device5> device;
    D3D12CreateDevice(Adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(device.ReleaseAndGetAddressOf()));

    return {Factory, Adapter.Get(), device.Get()};
}

GPUAdapterInfo GPUAdapter::GetAdapterInfo() const noexcept
{
    DXGI_ADAPTER_DESC1 adapterDesc;
    Adapter->GetDesc1(&adapterDesc);

    return {adapterDesc.VendorId, adapterDesc.DeviceId};
}

} // namespace rgpu