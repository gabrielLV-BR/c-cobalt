add_rules("mode.debug", "mode.release")

add_requires("glfw", { system = true })

set_languages("c99")

-- engine

target("cobalt")
    set_kind("binary")

    add_includedirs(
        "src/", 
        "vendor/"
    )

    add_files(
        "src/*.c",
        "src/**/*.c",
        "vendor/glad/glad.c",
        "vendor/stb/stb_image.c"
    )

    add_packages("glfw")

task("vendor")
    on_run("init")

    set_menu {
        usage = "xmake vendor",
        description = "Downloads and sets up vendor libraries",
        options = {}
    }
