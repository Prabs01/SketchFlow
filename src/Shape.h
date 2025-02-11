#pragma once
#ifdef _WIN32
    #include <SDL.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL2/SDL.h>  // Linux (also works for other Unix-like systems)
#endif

#include "Canvas.h"

class Shape
{
protected:
    Canvas* canvas;
public:
    Shape(/* args */);

    virtual void draw() = 0;
    virtual void clear() = 0;

    void setCanvas(Canvas* canvas);
    
    ~Shape();
};


class Line:public Shape{
    private:
        SDL_Point p1;
        SDL_Point p2;
        int size;

    public:
        Line();
        Line(SDL_Point p1, SDL_Point p2);
        Line(int x1, int y1, int x2, int y2);

        void draw() override;
        void clear() override;
        void move(int dx, int dy);
};

class Rectangle:public Shape{
    private:
        SDL_Point p1;
        SDL_Point p2;

    public:
        Rectangle();
        Rectangle(SDL_Point p1, SDL_Point p2);
        Rectangle(int x1, int y1, int x2, int y2);

        void draw() override;
        void clear() override;
        void move(int dx, int dy);
};
