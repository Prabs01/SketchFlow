#pragma once

#include<SDL.h>
#include<iostream>

using namespace std;

//to be changed for responsiveness
extern SDL_Rect CANVAS_RECT;

class Canvas
{
private:
    SDL_Renderer* renderer = nullptr;
    Uint32* pixels = nullptr;
    SDL_Rect area;
    SDL_Texture* canvaTexture = nullptr;
    SDL_Texture* bufferTexture = nullptr;
    Uint32* bufferPixels = nullptr;
    bool showBuffer;

public:
    Canvas();

    void init(SDL_Renderer* renderer_);

    void clear();
    void clearBuffer();

    void copyToBuffer();

    void updatePixels();
    void updateBuffer();

    void render();

    void setPixel(int x,int y,Uint32 color); 
    void setPixelBuffer(int x,int y,Uint32 color);

    void fitCanvas(int* x, int* y);

    Uint32 getPixelColor(int x , int y);
    Uint32 getPixelColorBuffer(int x , int y);

    int getXmax();
    int getXmin();
    int getYmin();
    int getYmax();

    bool isInside(int x, int y);

    void drawLine(int x1, int y1, int x2, int y2);
    void drawLineBuffer(int x1, int y1, int x2, int y2);

    void clearLine(int x1, int y1, int x2, int y2);
    void clearLineBuffer(int x1, int y1, int x2, int y2);

    void viewBuffer();
    void removeBuffer();

    ~Canvas();
};
