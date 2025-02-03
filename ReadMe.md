# SketchFlow

This is 

## Requirements

To run this project, you will need to have the following dependencies installed on your system:

- **SDL2**: The SDL2 library is required to create windows, handle input, and render graphics.

### Installing SDL2

- **macOS**: You can install SDL2 using Homebrew:
  ```bash
  brew install sdl2

- **windows**: 
Reference this video: SDL2 Setup Tutorial or Follow along these steps to set up SDL2 for your C++ project on Windows.

1. For downloading SDL2
Steps are as follows :

You may download the required release from the official SDL Github Repo here we download the Development Library : SDL2-devel-2.xx.xx-mingw.tar.gz
2. Extract the development library
Open command prompt and cd to your download location and type in :
'''bash
mkdir sdl

tar -xvzf SDL2-devel-2.xx.xx-mingw.tar.gz -C sdl
3. Copy the required files/folders to your graphics folder
copy the i686-w64-mingw32/include and i686-w64-mingw32/lib folders to your Graphics/src directory
copy the bin/SDL2.dll on same level as your src folder i.e. at Graphics folder
4. Write Your First SDL2 Program
Clone this repo, create a new C/C++ source file (e.g., main.cpp) and add the "sdl_custom_header.h" file given in this repo on top of your code by :

#include "sdl_custom_header.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

//I've created the drawFunc in the sdl_custom_header.h
void drawFunc(SDL_Renderer *renderer, float points[]){
    ...
}
int main(){
    ...

    float points[4] = {x1,y1,x2,y2};
    SDL_Start(points);
    return 0;
}
5. Compile your c/cpp code
You can do

g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
or you can use the Makefile

all:
    g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
If it still doesn't work, go to the C/C++ extension, and you could change the include path from ${default} to ${workspaceFolder}/**
