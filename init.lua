
local function setup_stb_image()
    import("net.http")

    local url = "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"

    cprint("${dim black}Downloading stb_image")

    local ok = http.download(url, "vendor/stb/stb_image.h")
end

local function setup_glad()
    local permalink = "https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.0&profile=core&loader=on&localfiles=on"
    cprint("\t${bright cyan} Download GLAD and extract it into vendor/glad from here: ${clear underline}%s", permalink)
end

function main()
    local stb_image = "vendor/stb/"
    local glad      = "vendor/glad/"
    local ok = true

    -- check for stb_image
    cprint("${dim black}- Checking stb_image")
    if not os.exists(stb_image) then
        ok = false
        cprint("\t${yellow} Not found")
        setup_stb_image()
    end

    -- check for glad
    cprint("${dim black}- Checking glad")
    if not os.exists(glad) then
        ok = false
        cprint("\t${yellow} Not found")
        setup_glad()
    end

    if ok then cprint("${bright green}Vendor setup done") end
end
