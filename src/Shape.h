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
        SDL_Point* vertices;   // Array of vertices (points)
        int numVertices; 
        SDL_Point p1; //center
        SDL_Point p2; //vertex
        int size;
        Color color;

    public:
        Polygon();
        Polygon(int numVertices, int x1, int y1, int x2, int y2, int size =3, Color color = black);
        
        void draw() override;
        void clear() override;

        void drawBuffer() override;
        void clearBuffer() override;

};

/*_________NOTE FOR SWAROOP_________
 - you MUST implement the virtual functions (draw(), clear(),etc..)of the parent class otherwise the program will not work.
 - make such that you can increases the line width and change the color of the shapes(take reference from line).
 - while testing you MUST CALL the setCanvas() function after making a shape object(after calling the constructor). Otherwise shape will not be able to access the canvas.
 - First try handling inputs in the main function event handler and if all things are working only then give a pull request.
*/

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
