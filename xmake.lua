add_requires("libsdl")

target("rgpuHelloTriangle")
    on_load(function()
        if not is_plat("windows") then
            cprint('${red}Other platform is working in progress')
        end
    end)

    add_packages("libsdl")

    set_languages("c++20")
    set_warnings("allextra")
    set_optimize("none")
    set_exceptions("no-cxx")

    add_includedirs("include")
    add_files("source/d3d12/*.cpp")
    add_syslinks("dxgi", "d3d12", "d3dcompiler")

    add_files("examples/HelloTriangle.cpp")