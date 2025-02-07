
#pragma once

#include<SDL.h>
#include<iostream>

#include"Color.h"

using namespace std;

//to define the rectangle where canvas is to be shown.
extern SDL_Rect CANVAS_RECT;


/*
 * The Canvas class allows you to draw, clear, and manipulate pixels on a 2D canvas. It uses SDL for rendering and 
 * supports operations like setting pixel colors, drawing lines, copying to buffers, and rendering the content.
 * It is equipped with a background color and allows for drawing on an offscreen buffer before displaying it on the screen.
 */
class Canvas
{
private:
    SDL_Renderer* renderer = nullptr;

    Uint32* pixels = nullptr;// this is the array(can be thought as matrix) of pixels with a Uint32 color(ARGB) value for each
    SDL_Rect area;
    SDL_Texture* canvaTexture = nullptr;
    SDL_Texture* bufferTexture = nullptr;
    Uint32* bufferPixels = nullptr;// pixel matrix for canvas's buffer. buffer is to be used when drawing shapes or to draw the cursor
    bool showBuffer;
    Color bgColor;

public:
    Canvas();

    void init(SDL_Renderer* renderer_);

    void clear();
    void clearBuffer();

    void copyToBuffer();

    void updatePixels();//is needed copy all the pixels to the canvaTexture and render it later
    void updateBuffer();

    void render();

    void setPixel(int x,int y,Color color); 
    void setPixelBuffer(int x,int y,Color color);

    void fitCanvas(int* x, int* y);/*by default the setPixel function takes the pixel positions relative to window.
                                     To specify pixel postion on the canvas call fitCanvas first*/ 

    Color getPixelColor(int x , int y);
    Color getPixelColorBuffer(int x , int y);

    int getXmax();
    int getXmin();
    int getYmin();
    int getYmax();

    bool isInside(int x, int y);

    void drawLine(int x1, int y1, int x2, int y2, Color color);
    void drawLineBuffer(int x1, int y1, int x2, int y2, Color color);

    void clearLine(int x1, int y1, int x2, int y2);
    void clearLineBuffer(int x1, int y1, int x2, int y2);

    void viewBuffer();
    void removeBuffer();

    ~Canvas();
};

