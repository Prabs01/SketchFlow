#pragma once
#ifdef _WIN32
    #include <SDL.h>
#elif __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL2/SDL.h>  // Linux (also works for other Unix-like systems)
#endif

#include "Canvas.h"
#include <cmath>
#include <vector>

class Shape
{
protected:
    Canvas* canvas;
public:
    Shape(/* args */);

    virtual void draw() = 0;
    virtual void clear() = 0;

    virtual void drawBuffer() = 0;
    virtual void clearBuffer()=0;

    void setCanvas(Canvas* canvas);
    
    ~Shape();
};


class Line:public Shape{
    private:
        SDL_Point p1;
        SDL_Point p2;
        int size;
        Color color;

    public:
        Line();
        Line(SDL_Point p1, SDL_Point p2, int size = 3, Color color = black);
        Line(int x1, int y1, int x2, int y2, int size =3, Color color = black);

        void drawLine(bool isBuffer, bool isClear);

        void draw() override;
        void clear() override;

        void drawBuffer() override;
        void clearBuffer() override;

        void move(int dx, int dy);

        void setEndingPoint(SDL_Point p2);
        void setEndingPoint(int x2, int y2);
        void setStartingPoint(SDL_Point p1);
        void setStartingPoint(int x1, int y1);
};

class Polygon:public Shape{
    private:
        // SDL_Point* vertices;   // Array of vertices (points)
        std::vector<SDL_Point> vertices; // Store all vertices
        SDL_Point tempPoint; // Current mouse position for preview
        int size;
        Color color;
        int numVertices; 
        SDL_Point p1; //center
        SDL_Point p2; //vertex


    public:
        Polygon();
        Polygon(int x, int y, int cx, int cy, int numVertices, int size = 3, Color color = black);        
        //
        void updateVertices(const std::vector<SDL_Point>& points, SDL_Point temp);
        void drawPolygon(bool isBuffer, bool isClear);

        void draw() override;
        void clear() override;
        void drawBuffer() override;
        void clearBuffer() override;

        // void generateVertices(int x, int y);
        void setEndingPoint(int x, int y);

};

// class Rectangle:public Shape{
//     private:
//         SDL_Point p1;
//         SDL_Point p2;

//     public:
//         Rectangle();
//         Rectangle(SDL_Point p1, SDL_Point p2);
//         Rectangle(int x1, int y1, int x2, int y2);

//         void draw() override;
//         void clear() override;
//         void move(int dx, int dy);
// };
