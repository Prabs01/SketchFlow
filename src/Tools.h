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
#include"Shape.h"


using namespace std;

// Define bounding boxes and image paths for tools

extern int nextGap; // Padding between boxes
extern int boxSize; // Size of each tool box
extern int padding; // Padding between tools in the grid
//3 (+55) + 4 (+55) +3
extern int vertical;
extern int horizontal;

extern SDL_Rect PENCIL_RECT;
extern SDL_Rect ERASER_RECT;
extern SDL_Rect FILLER_RECT;
extern SDL_Rect LINE_DRAWER_RECT;
extern SDL_Rect SELECT_TOOL_RECT;
extern SDL_Rect POLYGON_TOOL_RECT;
extern SDL_Rect RECTANGLE_TOOL_RECT;
extern SDL_Rect ELLIPSE_TOOL_RECT;


extern char PENCIL_IMAGE_URL[];
extern char ERASER_IMAGE_URL[];
extern char FILLER_IMAGE_URL[];
extern char LINE_DRAWER_IMAGE_URL[];
extern char SELECT_TOOL_IMAGE_URL[];
extern char POLYGON_TOOL_IMAGE_URL[];
extern char RECTANGLE_TOOL_IMAGE_URL[];
extern char ELLIPSE_TOOL_IMAGE_URL[];

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
    Color toolColor;

public:
    virtual void makeTexture(SDL_Renderer* renderer_) = 0;  //the makeTexture loads the tools image
    virtual void render() = 0;
    virtual void onMouseDown(SDL_Event& event) = 0;
    virtual void onMouseUp(SDL_Event& event) = 0;
    virtual void onMouseMove(SDL_Event& event) = 0;
    virtual void keyboardInput(SDL_Event& event) = 0;
    
    virtual void drawCursor() = 0;

    virtual void unSelect() = 0; // to rest the actions of the tools once unselected

    bool isMouseOver();
    void hover(); // Handles hover effects
    void clicked();
    void setCanvas(Canvas* canvas_);
    void setToolColor(Color color);
    SDL_Rect getBoundBox() const { return bound_box; } // Add this method
};

// Pencil tool for freehand drawing
class Pencil : public Tools {
private:
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
    void unSelect() override;
    void drawCursor() override;
    void setPixelSize(int pixelSize_);
};

// Eraser tool for removing pixels
class Eraser : public Tools {
private:
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
    void unSelect() override;

    void setEraserSize(int EraserSize_);
    void drawCursor() override;
};

// Filler tool for flood fill algorithm
class Filler : public Tools {
private:
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
    void unSelect() override;

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
    void unSelect() override;

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
    bool drawing;
    Line drawingLine;

public:
    LineDrawer();
    void makeTexture(SDL_Renderer* renderer) override;
    void render() override;
    void onMouseDown(SDL_Event& event) override;
    void onMouseUp(SDL_Event& event) override;
    void onMouseMove(SDL_Event& event) override;
    void drawCursor() override;
    void keyboardInput(SDL_Event& event) override;
    void unSelect() override;
};


class PolygonTool : public Tools {

    private:
        SDL_Point center, vertex;// Store the points of the polygon
        int noVertices;
        int width;
        bool isDrawing; // Track if the user is currently drawing
        Polygon polygon; // Polygon object for drawing
        bool isMoving = false;
        int prevX,prevY;
    
    
    public:
        PolygonTool(int numVertices);
        void makeTexture(SDL_Renderer* renderer_) override;
        void render() override;
        void onMouseDown(SDL_Event& event) override;
        void onMouseUp(SDL_Event& event) override;
        void onMouseMove(SDL_Event& event) override;
        void drawCursor() override;
        void keyboardInput(SDL_Event& event) override;
        void unSelect() override;
    };


class RectTool : public Tools {

    private:
        SDL_Point vertex1, vertex2;// Store the points of the polygon
        int width;
        bool isDrawing; // Track if the user is currently drawing
        Rectangle rectangle; // Polygon object for drawing
        bool isMoving = false;
        int prevX,prevY;
    
    public:
        RectTool();
        void makeTexture(SDL_Renderer* renderer_) override;
        void render() override;
        void onMouseDown(SDL_Event& event) override;
        void onMouseUp(SDL_Event& event) override;
        void onMouseMove(SDL_Event& event) override;
        void drawCursor() override;
        void keyboardInput(SDL_Event& event) override;
        void unSelect() override;
    };


class EllipseTool : public Tools {

    private:
        SDL_Point vertex1, vertex2;// Store the points of the polygon
        int width;
        bool isDrawing; // Track if the user is currently drawing
        Ellipse ellipse; // Polygon object for drawing
        bool isMoving = false;
        int prevX,prevY;
    
    public:
        EllipseTool();
        void makeTexture(SDL_Renderer* renderer_) override;
        void render() override;
        void onMouseDown(SDL_Event& event) override;
        void onMouseUp(SDL_Event& event) override;
        void onMouseMove(SDL_Event& event) override;
        void drawCursor() override;
        void keyboardInput(SDL_Event& event) override;
        void unSelect() override;
    };