add_rules("mode.debug", "mode.release")

target("rgpu")
    set_languages("c++20")
    set_warnings("allextra")
    set_optimize("aggressive")
    set_exceptions("no-cxx")

    add_includedirs("include")

    add_files("source/d3d12/*.cpp")
    add_links("dxgi", "d3d12", "d3dcompiler")

    add_files("examples/HelloTriangle.cpp")