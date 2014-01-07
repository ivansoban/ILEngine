## ILEngine

This a simple OpenGL Rendering Engine. It currently supports rendering 3D meshes
with basic support for textures and custom shader programs.

The goal is for the project to eventually become a more fully featured game engine
with support for lighting effects and physical interactions.

Currently, the Engine API is fully C++ but soon Python will be used as a language
for scripting the engine.

# Installation

The build system is CMake and building has only been tested on Mac OS X thus far
but will soon be more cross-platform.

Running the following should get you started:

```bash
cd ILEngine

mkdir build
cd build

cmake ..

make

make test

# This will show give you a look at the engine
./engine
```

# Dependencies

OpenGL/GLEW - Graphics
GLFW - Window Creation
ASSIMP - Mesh Loading
DevIL - Image/Texture Loading
