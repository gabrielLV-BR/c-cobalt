
local function setup_stb_image()
    import("net.http")

    local url = "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"

    cprint("${dim black}Downloading stb_image")

    local ok = http.download(url, "vendor/stb/stb_image.h")
    print(ok)
end

local function setup_glad()
    
end

function main()
    local stb_image = "vendor/stb/"
    local glad      = "vendor/glad/"

    -- check for stb_image
    cprint("${dim black}- Checking stb_image")
    if not os.exists(stb_image) then
        cprint("\t${yellow} Not found")
        setup_stb_image()
    end

    -- check for glad
    cprint("${dim black}- Checking glad")
    if not os.exists(glad) then
        cprint("\t${yellow} Not found")
        setup_glad()
    end

    cprint("${bright green}Vendor setup done")
end
