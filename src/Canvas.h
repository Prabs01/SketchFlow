#pragma once
#include<SDL.h>
#include<iostream>

#include"Color.h"

using namespace std;

// Defines the rectangle where the canvas is displayed
extern SDL_Rect CANVAS_RECT;

/*
 * The Canvas class provides functionalities to draw, clear, and manipulate pixels on a 2D canvas.
 * It maintains a background color, supports offscreen buffering, and allows pixel-level modifications.
 */
class Canvas
{

private:
    SDL_Renderer* renderer = nullptr;
    Uint32* pixels = nullptr; // Pixel array representing the canvas (ARGB format)
    SDL_Rect area;
    SDL_Texture* canvaTexture = nullptr;
    SDL_Texture* bufferTexture = nullptr;
    Uint32* bufferPixels = nullptr; // Pixel array for buffer (used for temporary drawings like cursor or shape previews)
    bool showBuffer;
    Color bgColor;

public:
    Uint32* pixels = nullptr;
    Canvas();
    Canvas(int SW,int SH);

    void init(SDL_Renderer* renderer_); // Initializes the canvas with an SDL renderer

    void clear(); // Clears the canvas
    void clearBuffer(); // Clears the buffer

    void copyToBuffer(); // Copies canvas pixels to buffer

    void updatePixels(); // Copies pixel data to the canvas texture
    void updateBuffer(); // Copies buffer pixel data to the buffer texture

    void render(); // Renders the canvas on the screen

    void setPixel(int x, int y, Color color); // Sets a pixel color on the canvas
    void setPixelBuffer(int x, int y, Color color); // Sets a pixel color in the buffer

    void fitCanvas(int* x, int* y); // Converts window-relative coordinates to canvas-relative coordinates

    Color getPixelColor(int x, int y); // Gets the color of a pixel on the canvas
    Color getPixelColorBuffer(int x, int y); // Gets the color of a pixel in the buffer

    int getXmax(); // Returns the max X-coordinate of the canvas
    int getXmin(); // Returns the min X-coordinate of the canvas
    int getYmin(); // Returns the min Y-coordinate of the canvas
    int getYmax(); // Returns the max Y-coordinate of the canvas

    bool isInside(int x, int y); // Checks if a point is inside the canvas bounds

    void drawLine(int x1, int y1, int x2, int y2, Color color); // Draws a line on the canvas
    void drawLineBuffer(int x1, int y1, int x2, int y2, Color color); // Draws a line on the buffer

    void clearLine(int x1, int y1, int x2, int y2); // Clears a line from the canvas
    void clearLineBuffer(int x1, int y1, int x2, int y2); // Clears a line from the buffer

    void viewBuffer(); // Displays the buffer
    void removeBuffer(); // Hides the buffer

    ~Canvas(); // Destructor to clean up resources
};
