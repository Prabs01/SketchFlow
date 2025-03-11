#pragma once
#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#else
    #include <SDL2/SDL.h>  // Linux (also works for other Unix-like systems)
    #include <SDL2/SDL_image.h>
#endif


#include <iostream>
#include<stack>
#include<cstring>
#include"Color.h"

using namespace std;

// Defines the rectangle where the canvas is displayed
extern SDL_Rect CANVAS_RECT;
extern bool horizontalToolbar;

/*
 * The Canvas class provides functionalities to draw, clear, and manipulate pixels on a 2D canvas.
 * It maintains a background color, supports offscreen buffering, and allows pixel-level modifications.
 */
class Canvas
{

private:
    SDL_Renderer* renderer = nullptr;
    Uint32* pixels = nullptr; // Pixel array representing the canvas (ARGB format)
    Uint32* bufferPixels = nullptr; // Pixel array for buffer (used for temporary drawings like cursor or shape previews)
    bool showBuffer;
    SDL_Rect area;
    SDL_Texture* canvasTexture = nullptr;
    SDL_Texture* bufferTexture = nullptr;
    Color bgColor;
    Color currentColor; // Current drawing color
    stack<Uint32*> undoStack;

public:    
    Canvas(int SW,int SH);
    void save2PNG(const std::string& filename);
    void init(SDL_Renderer* renderer_); // Initializes the canvas with an SDL renderer

    void clear(SDL_Rect portion = CANVAS_RECT); // Clears the sent rectangular portion
    void clearBuffer(SDL_Rect portion = CANVAS_RECT); // Clears the buffer

    void copyToBuffer(SDL_Rect copyArea = CANVAS_RECT);// Copies canvas pixels to buffer
    void copyToCanvas(SDL_Rect copyArea = CANVAS_RECT);// for sending buffer to canvas
    void moveBufferContent(int dx, int dy, SDL_Rect moveArea = CANVAS_RECT);

    void updatePixels(); // Copies pixel data to the canvas texture
    void updateBuffer(); // Copies buffer pixel data to the buffer texture

    void render(); // Renders the canvas on the screen

    void setPixel(int x, int y, Color color); // Sets a pixel color on the canvas
    void setPixelBuffer(int x, int y, Color color); // Sets a pixel color in the buffer

    void fitCanvas(int* x, int* y); // Converts window-relative coordinates to canvas-relative coordinates
    void absoluteCord(int* x, int* y); // Converts canvas-relative coordinates to window-relative coordinates

    Color getPixelColor(int x, int y); // Gets the color of a pixel on the canvas
    Color getPixelColorBuffer(int x, int y); // Gets the color of a pixel in the buffer

    Color getBackgroundColor();// get the background color of the canvas

    int getXmax(); // Returns the max X-coordinate of the canvas
    int getXmin(); // Returns the min X-coordinate of the canvas
    int getYmin(); // Returns the min Y-coordinate of the canvas
    int getYmax(); // Returns the max Y-coordinate of the canvas

    bool isInside(int x, int y); // Checks if a point is inside the canvas bounds
    bool isInside(SDL_Rect rect);

    void drawLine(int x1, int y1, int x2, int y2, Color color); // Draws a line on the canvas
    void drawLineBuffer(int x1, int y1, int x2, int y2, Color color); // Draws a line on the buffer

    void clearLine(int x1, int y1, int x2, int y2); // Clears a line from the canvas
    void clearLineBuffer(int x1, int y1, int x2, int y2); // Clears a line from the buffer

    void viewBuffer(); // Displays the buffer
    void removeBuffer(); // Hides the buffer

    void pushCanvas();//for undo function
    void popCanvas();

    void setCurrentColor(Color color) {
        currentColor = color; // Sets the current drawing color
    }

    Color getCurrentColor() const {
        return currentColor; // Returns the current drawing color
    }

    ~Canvas(); // Destructor to clean up resources
};
