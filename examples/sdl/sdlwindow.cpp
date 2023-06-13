#include <sdl/sdlwindow.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

SDLWindow::SDLWindow(const char* title, std::uint32_t width, std::uint32_t height) noexcept
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLWindowHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, static_cast<int>(width), static_cast<int>(height), SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_SysWMinfo windowinfo;
    SDL_GetWindowWMInfo(static_cast<SDL_Window*>(SDLWindowHandle), &windowinfo);
#ifdef _WIN32
    NativeWindowHandle = windowinfo.info.win.window;
#else
    #error Other platform is working in progress
#endif
}

SDLWindow::~SDLWindow() noexcept
{
    SDL_DestroyWindow(static_cast<SDL_Window*>(SDLWindowHandle));
    SDL_Quit();
}

bool SDLWindow::PollEvents() const noexcept
{
    static SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
        return false;

    return true;
}