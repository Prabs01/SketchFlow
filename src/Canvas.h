#pragma once

#include<SDL.h>

//to be changed for responsiveness
extern SDL_Rect CANVAS_RECT;

class Canvas
{
private:
    SDL_Renderer* renderer = nullptr;
    Uint32* pixels = nullptr;
    SDL_Rect area;
    SDL_Texture* canvaTexture = nullptr;


public:
    Canvas();

    void init(SDL_Renderer* renderer_);

    void clear();

    void updatePixels();
    void render();

    void setPixel(int x,int y,Uint32 color); 

    void fitCanvas(int* x, int* y);

    Uint32 getPixelColor(int x , int y);

    int getXmax();
    int getXmin();
    int getYmin();
    int getYmax();

    bool isInside(int x, int y);

    void drawLine(int x1, int y1, int x2, int y2);

    void clearLine(int x1, int y1, int x2, int y2);

    ~Canvas();
};
