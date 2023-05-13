// Example: Draw a triangle by using rgpu.

#include <rgpu/rgpu.hpp>

int main()
{
    // Initialize rgpu
    rgpu::GPUInstance instance({
        .IsEnableDebugLayer = true,
        .IsEnableValidation = true
    });
    rgpu::GPUAdapter adapter = instance.CreateAdapter();
    rgpu::GPUDevice device = adapter.CreateDevice();
}