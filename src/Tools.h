#pragma once

#include<SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include"Canvas.h"
#include"Shape.h"

using namespace std;

extern SDL_Rect PENCIL_RECT;
extern char PENCIL_IMAGE_URL[];

extern SDL_Rect ERASER_RECT;
extern char ERASER_IMAGE_URL[];

extern SDL_Rect FILLER_RECT;
extern char FILLER_IMAGE_URL[];

extern SDL_Rect LINE_DRAWER_RECT;
extern char LINE_DRAWER_IMAGE_URL[];

class Tools
{
protected:
    SDL_Texture* imgTexture = nullptr;
    SDL_Renderer* renderer = nullptr;
    Canvas* canvas = nullptr;
    SDL_Rect bound_box;


public:

    virtual void makeTexture(SDL_Renderer* renderer_)= 0;

    virtual void render() = 0;

    virtual void onMouseDown(SDL_Event& event)=0;
    virtual void onMouseUp(SDL_Event& event)=0;

    virtual void onMouseMove(SDL_Event& event)=0;

    virtual bool isMouseOver()=0;

    virtual void drawCursor()=0;


    void setCanvas(Canvas* canvas_);

};

class Pencil:public Tools{
    private:
        Uint32  toolColor = 0;
        int pixelSize;
        bool isDrawing;
        SDL_Point lastPos;

    public:
        Pencil();

        void makeTexture(SDL_Renderer* renderer)override;

        void render() override;
        void onMouseDown(SDL_Event& event) override;
        void onMouseUp(SDL_Event& event) override;
        void onMouseMove(SDL_Event& event) override;
        bool isMouseOver() override;

        void drawCursor() override;

        void setColor(Uint32 color);

        void setPixelSize(int pixelSize_);

};

class Eraser:public Tools{
    private:
        Uint32  toolColor;
        int eraserSize;
        bool isDrawing;
        SDL_Point lastPos;
        SDL_Rect eraserRect;

    public:

        Eraser();

        void makeTexture(SDL_Renderer* renderer)override;

        void render() override;
        void onMouseDown(SDL_Event& event) override;
        void onMouseUp(SDL_Event& event) override;
        void onMouseMove(SDL_Event& event) override;
        bool isMouseOver() override;

        void setColor(Uint32 color);

        void setEraserSize(int EraserSize_);

        void drawCursor() override;


};


class Filler:public Tools{
    private:
        Uint32 fill_color;
        Uint32 boundary_color;
        Uint32 current_color;
        bool pixelSelected;
        
    public:
        Filler();

        void makeTexture(SDL_Renderer* renderer)override;

        void render() override;
        void onMouseDown(SDL_Event& event) override;
        void onMouseUp(SDL_Event& event) override;
        void onMouseMove(SDL_Event& event) override;
        bool isMouseOver() override;
        void drawCursor() override;

        void setColor(Uint32 color);
        void setBoundaryColor(Uint32 color);
        void fill(int x, int y);
};

class Select:public Tools{

};

class LineDrawer:public Tools{
    private:
        SDL_Point startingPixel;
        SDL_Point endingPixel;
        int width;
        Uint32 color;
        bool drawing;

    public:
        LineDrawer();
        void makeTexture(SDL_Renderer* renderer)override;

        void render() override;
        void onMouseDown(SDL_Event& event) override;
        void onMouseUp(SDL_Event& event) override;
        void onMouseMove(SDL_Event& event) override;
        bool isMouseOver() override;
        void drawCursor() override;

        void setColor(Uint32 color);
};

