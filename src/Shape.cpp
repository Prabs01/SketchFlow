
#include "Shape.h"

Shape::Shape(){
    canvas = nullptr;
}

void Shape::setCanvas(Canvas* canvas_){
    canvas = canvas_;
}

Shape::~Shape(){
    free(canvas);
}


Line::Line(){
    p1 = {-100,-100};
    p2 = {-100, -100};
}

Line::Line(SDL_Point p1_, SDL_Point p2_){
    p1 = p1_;
    p2 = p2_;
}

Line::Line(int x1, int y1, int x2, int y2){
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
}

void Line::draw(){
    canvas->drawLine(p1.x, p1.y, p2.x, p2.y);
}
void Line::clear(){
    canvas->clearLine(p1.x, p1.y, p2.x, p2.y);
}

void Line::move(int dx, int dy){
    clear();
    p1.x += dx;
    p2.x += dx;
    p1.y += dy;
    p2.y += dy;
    draw();
}