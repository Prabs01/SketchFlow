#pragma once

#include<SDL.h>
#include"Canvas.h"
#include"ToolBar.h"

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
