#include "Shape.h"

Shape::Shape(){
    canvas = nullptr;
}

void Shape::setCanvas(Canvas* canvas_){
    canvas = canvas_;
}

/*############################### LINE ###############################*/

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
    p2.x = x2;
    p2.y = y2;
}

void Line::setEndingPoint(SDL_Point p){
    p2.x = p.x;
    p2.y = p.y;
}

/*############################### POLYGON ###############################*/

Polygon::Polygon(){ //def constructor
    numVertices = 3;
    p1 = {-100,-100};
    p2 = {-100, -100};
    size = 3;
}

void Polygon::generateVertices(int x, int y){
    int cx = p1.x;
    int cy = p1.y;
    
    float rad = sqrt( pow((x-cx), 2) + pow((y-cy), 2) );
    float angle = (2*M_PI)/numVertices ;
    
    vertices = (SDL_Point*)malloc(numVertices * sizeof(SDL_Point)); // Dynamically allocate memory
    if (vertices != NULL) {
        
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

        //translate back to original position
        for (int i = 0; i < numVertices; i++) {
            vertices[i].x = vertices[i].x + cx;
            vertices[i].y = vertices[i].y + cy;
        }
    }
    else{
        printf("Error : Failed to initialize the points!\n");
    }

}

Polygon::Polygon(int Vertices_, int cx, int cy, int x, int y, int size_, Color color_){
    numVertices = Vertices_;
    p1.x = cx;
    p1.y = cy;
    p2.x = x;
    p2.y = y;
    size = size_;
    color = color_;

    generateVertices(x,y);

}

void Polygon::drawPolygon(bool isBuffer, bool isClear) {
    
    Color colorToUse = isClear ? transparent : color;
    if(!isBuffer){
        colorToUse = isClear ? canvas->getBackgroundColor() : color;
    }

    for (int i = 0; i < numVertices; ++i) {
        int nextIndex = (i + 1) % numVertices; // Wrap around to the first vertex
        Line line(vertices[i].x, vertices[i].y, vertices[nextIndex].x, vertices[nextIndex].y, size, colorToUse);
        line.setCanvas(canvas);

        if (isBuffer) {
            line.drawBuffer(); // Draw to buffer
        } else {
            line.draw(); // Draw to canvas
        }
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
    generateVertices(x,y);
}

/*############################### RECTANGLE ###############################*/

void Rectangle::generateVertices(int x, int y) {
    vertices.resize(4);  // Use vector's resize() instead of malloc

    // Diagonal points are p1 (p1.x, p1.y) and (x, y)
    int x1 = p1.x, y1 = p1.y;
    int x2 = x, y2 = y;

    // Center of rectangle
    int centerX = (x1 + x2) / 2;
    int centerY = (y1 + y2) / 2;

    // Simplified width/height calculation
    float width = std::abs(x2 - x1);
    float height = std::abs(y2 - y1);

    // Rotation angle
    double angle = atan2(y2 - y1, x2 - x1);

    // Half dimensions
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    // Generate rotated vertices
    for (int i = 0; i < 4; i++) {
        float signX = (i % 2 == 0) ? -1 : 1;
        float signY = (i < 2) ? -1 : 1;

        // Relative positions
        float relX = signX * halfWidth;
        float relY = signY * halfHeight;

        // Rotated coordinates
        float rotatedX = centerX + relX * cos(angle) - relY * sin(angle);
        float rotatedY = centerY + relX * sin(angle) + relY * cos(angle);

        // Assign to vector
        vertices[i] = {static_cast<int>(rotatedX), static_cast<int>(rotatedY)};
    }
}


Rectangle::Rectangle(){ //def constructor
    p1 = {-100,-100};
    p2 = {-100, -100};
    size = 3;
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2, int size_ = 3, Color color_ = black){
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    size = size_;
    rectColor = color_;

    generateVertices(x2,y2);
}
        
void Rectangle::drawRectangle(bool isBuffer, bool isClear){

    Color colorToUse = isClear ? transparent : rectColor;
    if(!isBuffer){
        colorToUse = isClear ? canvas->getBackgroundColor() : rectColor;
    }

    for (int i = 0; i < 4; ++i) {
        int nextIndex = (i + 1) % 4; // Wrap around to the first vertex
        Line line(vertices[i].x, vertices[i].y, vertices[nextIndex].x, vertices[nextIndex].y, size, colorToUse);
        line.setCanvas(canvas);

        if (isBuffer) {
            line.drawBuffer(); // Draw to buffer
        } else {
            line.draw(); // Draw to canvas
        }
    }

}

void Rectangle::draw() {
    drawRectangle(false, false);
}
void Rectangle::clear() {
    drawRectangle(false, true);
}
void Rectangle::drawBuffer() {
    drawRectangle(true, false);
}
void Rectangle::clearBuffer() {
    drawRectangle(true, true);
}

void Rectangle::setEndingPoint(int x, int y){   //for use from Tools.cpp
    generateVertices(x,y);
}



/*
############################### ELLIPSE ###############################

void Rectangle::generateVertices(int x, int y){

}

Rectangle::Rectangle(int x1, int y1, int x2, int y2, int size_ = 3, Color color_ = black){
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    size = size_;
    rectColor = color_;

    generateVertices(x2,y2);
}
        
void Rectangle::drawRectangle(bool isBuffer, bool isClear){

    Color colorToUse = isClear ? transparent : rectColor;
    if(!isBuffer){
        colorToUse = isClear ? canvas->getBackgroundColor() : color;
    }

    for (int i = 0; i < 4; ++i) {
        int nextIndex = (i + 1) % 4; // Wrap around to the first vertex
        Line line(vertices[i].x, vertices[i].y, vertices[nextIndex].x, vertices[nextIndex].y, size, colorToUse);
        line.setCanvas(canvas);

        if (isBuffer) {
            line.drawBuffer(); // Draw to buffer
        } else {
            line.draw(); // Draw to canvas
        }
    }

}

void Rectangle::draw() {
    drawRectangle(false, false);
}
void Rectangle::clear() {
    drawRectangle(false, true);
}
void Rectangle::drawBuffer() {
    drawRectangle(true, false);
}
void Rectangle::clearBuffer() {
    drawRectangle(true, true);
}

void Rectangle::setEndingPoint(int x, int y){   //for use from Tools.cpp
    generateVertices(x,y);
}
*/