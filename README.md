# About SketchFlow

SketchFlow is a simple and intuitive paint application built using SDL2 (Simple DirectMedia Layer 2). It allows users to draw and create digital artwork with basic painting tools. Whether you're sketching out ideas or just doodling for fun, SketchFlow provides an easy-to-use interface for creating and saving your drawings.

## Requirements

To run this project, you will need to have the following dependencies installed on your system:

- **SDL2**: The SDL2 library is required to create windows, handle input, and render graphics.

## Installing SDL2

### MacOS:
You can install SDL2 using Homebrew:
```bash
brew install sdl2
```

### Windows: 

Reference this video: [SDL2 Setup Tutorial](https://youtu.be/H08t6gD1Y1E?si=pC5MXzJEne0Wvq5A) or Follow along these steps to set up SDL2 on **Windows**.

1. For downloading SDL2
Steps are as follows :
- You may download the required release from the official [SDL Github Repo](https://github.com/libsdl-org/SDL/releases) here we download the Development Library : SDL2-devel-2.xx.xx-mingw.tar.gz

2. Extract the development library
Open command prompt and cd to your download location and type in :
```cmd
mkdir sdl

tar -xvzf SDL2-devel-2.xx.xx-mingw.tar.gz -C sdl
```

3. Copy the required files/folders to your graphics folder
- copy the i686-w64-mingw32/**include** and i686-w64-mingw32/**lib** folders to your Graphics/src  directory
- copy the bin/**SDL2.dll** on same level as your src folder i.e. at Graphics folder


**Enjoy SketchFlow ;)**