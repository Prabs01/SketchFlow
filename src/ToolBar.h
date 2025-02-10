#pragma once

#include<SDL.h>
#include"Tools.h"
#include"Canvas.h"
#include<vector>



class ToolBar
{
private:
    SDL_Rect area;
    Tools* activeTool;
    vector<Tools*> tools;
    SDL_Renderer* renderer;
    Canvas* canvas= nullptr;

public:
    ToolBar();
    ToolBar(int SW, int SH);

    void setRenderer(SDL_Renderer* renderer_);

    void setToolCanvas(Canvas* canvas_);

    void render();

    bool mouseClicked(SDL_Event& event);

    void handleEvent(SDL_Event& event);

    ~ToolBar();
    
};


