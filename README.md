# Cobalt

**Cobalt** is a Game Engine that will probably be forever in-development

I'm making this as a way to study and test myself on whether I can make this sort-of stuff in C

It currently lacks basic behaviour that you'd expect from an engine, but we're baby-crawling there

# Features

- It can render stuff

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

Make sure you have `git`, `glfw` system packages, adequate drivers for `opengl` and `xmake`

- Clone the repo
- Run `xmake` to build
- Run `xmake run` to run

Should be that simple, although it currently isn't