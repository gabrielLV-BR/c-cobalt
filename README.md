# Cobalt

**Cobalt** is a Game Engine that will probably be forever in-development

I'm making this as a way to study and test myself on whether I can make this sort-of stuff in C

It currently lacks basic behaviour that you'd expect from an engine, but we're baby-crawling there

# Features

- It can render stuff
- It can't for the life of it load models

That's about it :thumbsup:

# Future awaits

- More capable rendering system
- Batching for geometry with same materials
- Caching of shader uniforms 
- More capable mesh loading from file
- Lua files describing objects for dynamic loading
    - Hot reaload would be cool
- Complete Scene system for loading and storing scenes into files
    - Scripting for some scene interaction

It should be clear by this list that I'm very lost but very passionate about this so I'm probably overshooting.

# How to run

> :warning: Currently, even I'm having problems with this

Make sure you have `git`, `cmake`, `glfw` system packages and adequate drivers for `opengl`

- Clone the repo and `cd` into it
- Run `cmake -S . -B build` to create the build files inside `build/`
- `cd` into `build/`
- Run `make` and run `cobalt` target

Currently, there's also the need to symlink the `assets/` folder in the project's root to `build/assets/`, so the built target can access it. (May fix it later)