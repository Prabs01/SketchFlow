#pragma once
#ifdef _WIN32
    #include <SDL.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL2/SDL.h>  // Linux (also works for other Unix-like systems)
#endif

#include"Tools.h"
#include"Canvas.h"

#include<vector>



/*
* The ToolBar class allows you to select different tools and call the functions of the activeTool.
* It also renders the tool icons and handle to inputs of the active tools as well as listens for click for other tools.
* The tools are pushed to the tools vector and activeTool points to the selected tool.
*/

class ToolBar
{
private:
    SDL_Rect area;
    Tools* activeTool;
    vector<Tools*> tools;
    SDL_Renderer* renderer;
    Canvas* canvas= nullptr;
    Color bgcolor;

public:
    ToolBar();
    ToolBar(int SW, int SH);

    void setRenderer(SDL_Renderer* renderer_);

    void setToolCanvas(Canvas* canvas_);

    void render();

    bool mouseClicked(SDL_Event& event); // listens for the clicks to the tools icon

    void handleEvent(SDL_Event& event);// handles the input for the active tool. 
    //tools only know what to do. not what the user inputs
    //commands the tools what to do.

    ~ToolBar();
    
};


