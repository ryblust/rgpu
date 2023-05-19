#pragma once

#include <cstdint>

class SDLWindow final {
public:
    SDLWindow(const char* title, std::uint32_t width, std::uint32_t height) noexcept;
    ~SDLWindow() noexcept;
    bool PollEvents() const noexcept;
    void* NativeWindowHandle;
private:
    void* SDLWindowHandle; // SDL_Window*
};