import os
import io
import requests
import zipfile
from urllib.request import urlretrieve

# Functions

def ensure_folder_exists(folder: str):
    if not os.path.isdir(folder):
        os.mkdir(folder)
        return False
    return len(os.listdir(folder)) > 0

def setup_stb(folder: str):
    stb_h = folder + "stb_image.h"
    stb_c = folder + "stb_image.c"

    url = "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"

    urlretrieve(url, stb_h)

    with open(stb_c, "w") as file:
        file.write("""

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

        """.strip())

def setup_glad(folder: str, version: tuple[int, int]):
    base = "https://glad.dav1d.de"

    options = {
        "language": "c",
        "specification" : "gl",
        "profile" : "core",
        "api" : "gl=" + ".".join(str(x) for x in version),
        "loader" : "on",
        "localfiles" : "on"
    }

    print(options)

    url = base + "/generate"

    response = requests.post(
        url, 
        data=options, 
        headers={
            "Content-Type" : "application/x-www-form-urlencoded",
        }
    )

    location = response.headers["Location"]

    url = base + location

    file = folder + "glad.zip"

    urlretrieve(url, file)

    with zipfile.ZipFile(file, "r") as z:
        z.extractall(folder)

# Checks to see if folders exist

stb_folder = "vendor/stb/"
glad_folder = "vendor/glad/"

ensure_folder_exists("vendor/")

if not ensure_folder_exists(stb_folder):
    print("Setting up stb...")
    setup_stb(stb_folder)
    print("Done")


if not ensure_folder_exists(glad_folder):
    print("Setting up glad...")
    setup_glad(glad_folder, (4, 0))
    print("Done")
