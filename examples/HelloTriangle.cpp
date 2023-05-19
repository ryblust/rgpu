// Example: Draw a triangle by using rgpu.

#include <rgpu/rgpu.hpp>

#include "utility/SDLWindow.hpp"

struct Vertex final {
    float position[4];
    float color[4];
};

int main()
{
    constexpr std::uint32_t width = 1280;
    constexpr std::uint32_t height = 720;

    // Create a window for rgpu to draw
    SDLWindow window{"rgpuHelloTriangle", width, height};

    // Create an Instance, Adapter, Device and a SwapChain
    auto instance = rgpu::GPUInstance{{
        .IsEnableDebugLayer = false,
        .IsEnableValidation = false
    }};

    auto adapter = instance.CreateAdapter();
    auto device = adapter.CreateDevice();

    auto swapchain = device.CreateSwapChain({
        .Width = width,
        .Height = height,
        .Format = rgpu::SwapChainFormatRGBA8UNorm,
        .BackBufferCount = 3,
        .PresentQueue = device.GraphicsQueue,
        .Surface = window.NativeWindowHandle
    });

    // Create vertices and a vertex buffer
    constexpr Vertex vertices[3]{};

    auto vertexbuffer = device.CreateBuffer({
        .Size = 3 * sizeof(Vertex),
        .State = rgpu::BufferStateGenericRead,
        .Usage = rgpu::BufferUsageVertex,
        .MemoryUsage = 0
    });

    // Upload vertices to video memory
    void* const vbAddress = vertexbuffer.Map();
    memcpy(vbAddress, vertices, sizeof(vertices));
    vertexbuffer.Unmap();

    // Create a render pass and record render commands
}