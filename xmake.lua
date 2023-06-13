add_rules("mode.debug", "mode.release", "plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
set_policy("build.optimization.lto", true)

add_requires("libsdl")

set_languages("c++20")
set_warnings("allextra")
set_exceptions("no-cxx")

add_cxxflags("/GS-", "/GR-", {tools = {"cl", "clang_cl"}})
add_cxxflags("/fno-rtti", {tools = {"clang", "gcc"}})

target("rgpu")
    set_kind("static")
    add_includedirs("include")
    add_files("source/rgpu_d3d12.cpp")
    add_syslinks("dxgi", "d3d12")

target("sdlwindow")
    set_kind("static")
    add_packages("libsdl")
    add_includedirs("examples")
    add_files("examples/sdl/sdlwindow.cpp")

target("HelloTriangle")
    add_deps("rgpu", "sdlwindow")
    add_includedirs("include", "examples")
    add_files("examples/HelloTriangle.cpp")