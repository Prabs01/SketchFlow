#pragma once

#include<SDL.h>
#include"Tools.h"
#include"Canvas.h"
#include<vector>

extern SDL_Rect TOOLBAR_RECT;

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

    void setRenderer(SDL_Renderer* renderer_);

    void setToolCanvas(Canvas* canvas_);

    void render();

    bool mouseClicked(SDL_Event& event);

    void handleEvent(SDL_Event& event);

    ~ToolBar();
    
};


