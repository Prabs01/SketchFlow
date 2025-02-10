#pragma once
#ifdef _WIN32
    #include <SDL.h>
#elif __APPLE__
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>  // Linux (also works for other Unix-like systems)
#endif

#include "Canvas.h"
#include "ToolBar.h"

class Controller
{
private:
    SDL_Event event;
    Canvas* canvas;
    ToolBar* toolbar;
    SDL_Renderer* renderer;
 
public:
    Controller();

    void handleInput();


    ~Controller();
};
