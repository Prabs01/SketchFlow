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
#include <vector>
#include "Canvas.h"
#include "Shape.h"
#include "Color.h"


using namespace std;

// Define bounding boxes and image paths for tools
extern SDL_Rect PENCIL_RECT;
extern char PENCIL_IMAGE_URL[];

extern SDL_Rect ERASER_RECT;
extern char ERASER_IMAGE_URL[];

extern SDL_Rect FILLER_RECT;
extern char FILLER_IMAGE_URL[];

extern SDL_Rect LINE_DRAWER_RECT;
extern char LINE_DRAWER_IMAGE_URL[];

extern SDL_Rect SELECT_TOOL_RECT;
extern char SELECT_TOOL_IMAGE_URL[];

/*
 * Base class for all tools.
 * Provides common functionality such as texture management, event handling, and hover effects.
 */
class Tools {
protected:
    SDL_Texture* imgTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    Canvas* canvas = nullptr;
    SDL_Rect bound_box;

public:
    virtual void makeTexture(SDL_Renderer* renderer_) = 0;
    virtual void render() = 0;
    virtual void onMouseDown(SDL_Event& event) = 0;
    virtual void onMouseUp(SDL_Event& event) = 0;
    virtual void onMouseMove(SDL_Event& event) = 0;
    virtual void keyboardInput(SDL_Event& event) = 0;
    
    virtual void drawCursor() = 0;

    bool isMouseOver();
    void hover(); // Handles hover effects
    void setCanvas(Canvas* canvas_);
};

// Pencil tool for freehand drawing
class Pencil : public Tools {
private:
    Color toolColor;
    int pixelSize;
    bool isDrawing;
    SDL_Point lastPos;

public:
    Pencil();
    void makeTexture(SDL_Renderer* renderer) override;
    void render() override;
    void onMouseDown(SDL_Event& event) override;
    void onMouseUp(SDL_Event& event) override;
    void onMouseMove(SDL_Event& event) override;
    void keyboardInput(SDL_Event& event) override;
    void drawCursor() override;
    void setColor(Color color);
    void setPixelSize(int pixelSize_);
};

// Eraser tool for removing pixels
class Eraser : public Tools {
private:
    Color toolColor;
    int eraserSize;
    bool isDrawing;
    SDL_Point lastPos;
    SDL_Rect eraserRect;

public:
    Eraser();
    void makeTexture(SDL_Renderer* renderer) override;
    void render() override;
    void onMouseDown(SDL_Event& event) override;
    void onMouseUp(SDL_Event& event) override;
    void onMouseMove(SDL_Event& event) override;
    void keyboardInput(SDL_Event& event) override;

    void setColor(Color color);
    void setEraserSize(int EraserSize_);
    void drawCursor() override;
};

// Filler tool for flood fill algorithm
class Filler : public Tools {
private:
    Color fill_color;
    Color boundary_color;
    Color current_color;
    bool pixelSelected;

public:
    Filler();
    void makeTexture(SDL_Renderer* renderer) override;
    void render() override;
    void onMouseDown(SDL_Event& event) override;
    void onMouseUp(SDL_Event& event) override;
    void onMouseMove(SDL_Event& event) override;
    void drawCursor() override;
    void keyboardInput(SDL_Event& event) override;

    void setColor(Color color);
    void setBoundaryColor(Color color);
    void fill(int x, int y); // Fills a region with the selected color
};

// Selection tool (implementation pending)
class SelectTool : public Tools {
private:
    SDL_Rect clipRect; // this is the rectangle of the select tool
    bool isSelecting; // tracks when the region is being selected
    bool isSelected; // tracks if the region is selected or or not
    SDL_Point lastMousePos;
    Color clipRectColor;

public:
    SelectTool();
    void makeTexture(SDL_Renderer* renderer) override;
    void render() override;
    void onMouseDown(SDL_Event& event) override;
    void onMouseUp(SDL_Event& event) override;
    void onMouseMove(SDL_Event& event) override;
    void drawCursor() override;
    void keyboardInput(SDL_Event& event) override;

    void drawClipRect();
    void clearClipRect();  //clearing clipRect is neccessary to move the selected part and clear the rectangle from buffer
    bool isCursorInside();

};

// Line drawer tool for creating straight lines
class LineDrawer : public Tools {
private:
    SDL_Point startingPixel;
    SDL_Point endingPixel;
    int width;
    Color color;
    bool drawing;

public:
    LineDrawer();
    void makeTexture(SDL_Renderer* renderer) override;
    void render() override;
    void onMouseDown(SDL_Event& event) override;
    void onMouseUp(SDL_Event& event) override;
    void onMouseMove(SDL_Event& event) override;
    void drawCursor() override;
    void keyboardInput(SDL_Event& event) override;
    void setColor(Color color);
};