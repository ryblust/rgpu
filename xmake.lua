add_rules("mode.debug", "mode.release")

target("Rage")
    set_languages("c++20")
    set_warnings("allextra")
    set_optimize("none")

    add_includedirs("inc")
    add_files("src/d3d12/*.cpp")
    add_files("Main.cpp")