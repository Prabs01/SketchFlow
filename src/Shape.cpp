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
    size = 3;
}

Line::Line(SDL_Point p1_, SDL_Point p2_, int size_, Color color_){
    p1 = p1_;
    p2 = p2_;
    size = size_;
    color= color_;
}

Line::Line(int x1, int y1, int x2, int y2, int size_, Color color_){
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    size = size_;
    color = color_;
}

void Line::drawLine(bool isBuffer, bool isClear) {
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);

    int ix = (p1.x < p2.x) ? 1 : -1;
    int iy = (p1.y < p2.y) ? 1 : -1;

    int x = p1.x;
    int y = p1.y;

    // Choose the pixel color based on whether it's drawing or clearing
    void (Canvas::*pixelFunc)(int, int, Color) = isBuffer ? &Canvas::setPixelBuffer : &Canvas::setPixel;
    
    Color colorToUse = isClear ? transparent : color;
    if(!isBuffer){
        Color colorToUse = isClear ? canvas->getBackgroundColor() : color;
    }

    if (dx >= dy) {  // Case where x changes more than y
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    (canvas->*pixelFunc)(x + xp, y + yp, colorToUse);
                }
            }
            if (p < 0) {
                p += 2 * dy;
            } else {
                y += iy;
                p += 2 * dy - 2 * dx;
            }
            x += ix;
        }
    } else {  // Case where y changes more than x
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    (canvas->*pixelFunc)(x + xp, y + yp, colorToUse);
                }
            }
            if (p < 0) {
                p += 2 * dx;
            } else {
                x += ix;
                p += 2 * dx - 2 * dy;
            }
            y += iy;
        }
    }
}

void Line::draw() {
    drawLine(false, false);  // Main canvas, drawing
}

void Line::clear() {
    drawLine(false, true);  // Main canvas, clearing
}

void Line::drawBuffer() {
    drawLine(true, false);  // Buffer, drawing
}

void Line::clearBuffer() {
    drawLine(true, true);  // Buffer, clearing
}

void Line::move(int dx, int dy){
    clear();
    p1.x += dx;
    p2.x += dx;
    p1.y += dy;
    p2.y += dy;
    draw();
}

void Line::setStartingPoint(int x1, int y1){
    p1.x = x1;
    p1.y = y1;
}

void Line::setStartingPoint(SDL_Point p){
    p1.x = p.x;
    p1.y = p.y;
}

void Line::setEndingPoint(int x2, int y2){
    // printf("helloo\n");
    // fflush(stdout);
    p2.x = x2;
    p2.y = y2;
    // printf("helloo2\n");
    // fflush(stdout);
}

void Line::setEndingPoint(SDL_Point p){
    p2.x = p.x;
    p2.y = p.y;
}


Polygon::Polygon(){ //def constructor
    numVertices = 3;
    p1 = {-100,-100};
    p2 = {-100, -100};
    size = 3;
}

// void Polygon::generateVertices(int x, int y){
//     int cx = p1.x;
//     int cy = p1.y;

// }

Polygon::Polygon(int x, int y, int cx, int cy, int Vertices_, int size_, Color color_){
    numVertices = Vertices_;
    p1.x = cx;
    p1.y = cy;
    p2.x = x;
    p2.y = y;
    size = size_;
    color = color_;

    // generateVertices(x,y);
    float rad = sqrt( pow((x-cx), 2) + pow((y-cy), 2) );
    float angle = (2*M_PI)/numVertices ;
    
// Replace with vector operations
    vertices.resize(numVertices);
    if (!vertices.empty()) {
        
        double rotAngle = atan2((double)(y - cy), (x - cx));  // atan2 handles vertical lines correctly

        //find coordinates w.r.t. axes
        for (int i = 0; i < numVertices; i++) {
            vertices[i].x = rad*cos(angle*i); // Copy points into the allocated array
            vertices[i].y = rad*sin(angle*i); // Copy points into the allocated array
        }

        //rotate back to its original coordinates
        for (int i = 0; i < numVertices; i++) {
             float tempx = vertices[i].x*cos(rotAngle) - vertices[i].y*sin(rotAngle);
             float tempy = vertices[i].x*sin(rotAngle) + vertices[i].y*cos(rotAngle);
             vertices[i].x = tempx;
             vertices[i].y = tempy;
        }

        //translate back to og position
        for (int i = 0; i < numVertices; i++) {
            vertices[i].x = vertices[i].x + cx;
            vertices[i].y = vertices[i].y + cy;
        }

    }
    else{
        printf("Error : Failed to initialize the points!\n");
    }

}

void Polygon::updateVertices(const std::vector<SDL_Point>& points, SDL_Point temp) {
    vertices = points;
    tempPoint = temp;
}

void Polygon::drawPolygon(bool isBuffer, bool isClear) {
    if (vertices.empty()) return;

    // Color colorToUse = isClear ? transparent : color;
    Color colorToUse = isClear ? transparent : color;
    if (!isBuffer) {
        colorToUse = isClear ? canvas->getBackgroundColor() : color;
    }
// Use colorToUse when setting pixels
    void (Canvas::*drawFunc)(int, int, int, int, int, Color) = isBuffer ? &Canvas::drawLineBuffer : &Canvas::drawLine;

    // Draw lines between all vertices
    for (size_t i = 1; i < vertices.size(); ++i) {
        (canvas->*drawFunc)(vertices[i-1].x, vertices[i-1].y, vertices[i].x, vertices[i].y, size, colorToUse);
    }

    // Draw temporary line to current mouse position
    if (!vertices.empty() && tempPoint.x != -1) {
        (canvas->*drawFunc)(vertices.back().x, vertices.back().y, tempPoint.x, tempPoint.y, size, colorToUse);
    }
}

void Polygon::draw() {
    drawPolygon(false, false);  // Main canvas, drawing
}

void Polygon::clear() {
    drawPolygon(false, true);  // Main canvas, clearing
}

void Polygon::drawBuffer() {
    drawPolygon(true, false);  // Buffer, drawing
}

void Polygon::clearBuffer() {
    drawPolygon(true, true);  // Buffer, clearing
}

void Polygon::setEndingPoint(int x, int y){
    Polygon(x, y, p1.x, p1.y, numVertices, size, color);
}