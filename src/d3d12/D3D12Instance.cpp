#include <Rage/Instance.hpp>
#include <Rage/D3D12/D3D12Backend.hpp>

namespace Rage
{

// struct GPUInstance::GPUInstanceImpl final
// {
//     GPUInstanceImpl(bool isEnableDebugLayer) noexcept
//     {
//         UINT dxgiCreateFlag = 0;

//         if (isEnableDebugLayer)
//         {
//             dxgiCreateFlag = DXGI_CREATE_FACTORY_DEBUG;
//             ID3D12Debug* debugger;
//             D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));

//             debugger->EnableDebugLayer();
//             debugger->Release();
//         }

//         CreateDXGIFactory2(dxgiCreateFlag, IID_PPV_ARGS(Factory.ReleaseAndGetAddressOf()));
//     }

//     Microsoft::WRL::ComPtr<IDXGIFactory6> Factory;
// };

GPUInstance::GPUInstance(bool isEnableDebugLayer) noexcept
{
    Instance = std::make_unique<GPUInstanceImpl>(isEnableDebugLayer);
}

GPUAdapter GPUInstance::CreateAdapter() const noexcept
{
    return Instance->Factory.Get();
}

} // namespace Rage