// Example: Draw a triangle by rgpu.

#include <rgpu/rgpu.hpp>
#include <sdl/sdlwindow.hpp>

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

    // Create an Instance, Device and a SwapChain
    auto instance = rgpu::Instance({
        .IsEnableDebugLayer = false,
        .IsEnableValidation = false
    });

    auto device = instance.CreateDevice();

    auto swapchain = device.CreateSwapChain({
        .Width = width,
        .Height = height,
        .Format = rgpu::SwapChainFormat::RGBA8UNorm,
        .BackBufferCount = 3,
        .PresentQueue = device.GraphicsQueue,
        .Surface = window.NativeWindowHandle
    });

    // Create vertices and a vertex buffer
    constexpr Vertex vertices[3]{};

    auto vertexbuffer = device.CreateBuffer({
        .Size = 3 * sizeof(Vertex),
        .State = rgpu::BufferState::GenericRead,
        .Usage = rgpu::BufferUsage::Vertex,
        .MemoryUsage = rgpu::MemoryUsage::CpuToGpu
    });

    // Upload vertices to video memory
    void* const vbAddress = vertexbuffer.Map(0, 0);
    memcpy(vbAddress, vertices, sizeof(vertices));
    vertexbuffer.Unmap();

    while (window.PollEvents())
        swapchain.Present();

    // Create a render pass and record render commands
}