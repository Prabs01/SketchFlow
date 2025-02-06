#pragma once
#include<SDL.h>
#include"Canvas.h"

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

    public:
        Line();
        Line(SDL_Point p1, SDL_Point p2);
        Line(int x1, int y1, int x2, int y2);

        void draw() override;
        void clear() override;
        void move(int dx, int dy);
};

