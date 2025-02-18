
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


void Line::draw(){
    int dx = abs(p2.x-p1.x);
    int dy = abs(p2.y-p1.y);

    int ix = (p1.x<p2.x)?1:-1;
    int iy = (p1.y<p2.y)?1:-1;

    int x = p1.x;
    int y = p1.y;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){

             for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixel(pixelX, pixelY, color);
                }
            }
            if(p<0){
                x = x+ix;
                p = p + 2*dy;
            }
            else if(p>=0){
                x = x+ix;
                y = y+iy;
                p = p + 2*dy -2*dx;
            }
        }
    }
    else if(dy>dx){
        int p = 2*dx - dy;
        for(int i = 0; i < dy; i++){
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixel(pixelX, pixelY, color);
                }
            }
            if(p<0){
                y = y+iy;
                p = p + 2*dx;
            }
            else if(p>=0){
                y = y+iy;
                x = x+ix;
                p = p + 2*dx -2*dy;
            }
        }
    }
}
void Line::clear(){
    int dx = abs(p2.x-p1.x);
    int dy = abs(p2.y-p1.y);

    int ix = (p1.x<p2.x)?1:-1;
    int iy = (p1.y<p2.y)?1:-1;

    int x = p1.x;
    int y = p1.y;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){

             for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixel(pixelX, pixelY, canvas->getBackgroundColor());
                }
            }
            if(p<0){
                x = x+ix;
                p = p + 2*dy;
            }
            else if(p>=0){
                x = x+ix;
                y = y+iy;
                p = p + 2*dy -2*dx;
            }
        }
    }
    else if(dy>dx){
        int p = 2*dx - dy;
        for(int i = 0; i < dy; i++){
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixel(pixelX, pixelY, canvas -> getBackgroundColor());
                }
            }
            if(p<0){
                y = y+iy;
                p = p + 2*dx;
            }
            else if(p>=0){
                y = y+iy;
                x = x+ix;
                p = p + 2*dx -2*dy;
            }
        }
    }
}

void Line::drawBuffer(){
    int dx = abs(p2.x-p1.x);
    int dy = abs(p2.y-p1.y);

    int ix = (p1.x<p2.x)?1:-1;
    int iy = (p1.y<p2.y)?1:-1;

    int x = p1.x;
    int y = p1.y;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){

             for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixelBuffer(pixelX, pixelY, color);
                }
            }
            if(p<0){
                x = x+ix;
                p = p + 2*dy;
            }
            else if(p>=0){
                x = x+ix;
                y = y+iy;
                p = p + 2*dy -2*dx;
            }
        }
    }
    else if(dy>dx){
        int p = 2*dx - dy;
        for(int i = 0; i < dy; i++){
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixelBuffer(pixelX, pixelY, color);
                }
            }
            if(p<0){
                y = y+iy;
                p = p + 2*dx;
            }
            else if(p>=0){
                y = y+iy;
                x = x+ix;
                p = p + 2*dx -2*dy;
            }
        }
    }
}

void Line::clearBuffer(){
    int dx = abs(p2.x-p1.x);
    int dy = abs(p2.y-p1.y);

    int ix = (p1.x<p2.x)?1:-1;
    int iy = (p1.y<p2.y)?1:-1;

    int x = p1.x;
    int y = p1.y;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){

             for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixelBuffer(pixelX, pixelY, transparent);
                }
            }
            if(p<0){
                x = x+ix;
                p = p + 2*dy;
            }
            else if(p>=0){
                x = x+ix;
                y = y+iy;
                p = p + 2*dy -2*dx;
            }
        }
    }
    else if(dy>dx){
        int p = 2*dx - dy;
        for(int i = 0; i < dy; i++){
            for (int yp = 0; yp < size; ++yp) {
                for (int xp = 0; xp < size; ++xp) {
                    int pixelX = x + xp;
                    int pixelY = y + yp;

                    canvas->setPixelBuffer(pixelX, pixelY, transparent);
                }
            }
            if(p<0){
                y = y+iy;
                p = p + 2*dx;
            }
            else if(p>=0){
                y = y+iy;
                x = x+ix;
                p = p + 2*dx -2*dy;
            }
        }
    }
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
    printf("helloo\n");
    fflush(stdout);
    p2.x = x2;
    p2.y = y2;
    printf("helloo2\n");
    fflush(stdout);
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

Polygon::Polygon(int Vertices_, int cx, int cy, int x, int y, int size_, Color color_){
    numVertices = Vertices_;
    p1.x = cx;
    p1.y = cy;
    p2.x = x;
    p2.y = y;
    size = size_;
    color = color_;

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

        //translate back to og position
        for (int i = 0; i < numVertices; i++) {
            vertices[i].x = vertices[i].x + cx;
            vertices[i].y = vertices[i].y + cy;
        }
        printf("Success : Initialized the points!\n");
        fflush(stdout);
    }
    else{
        printf("Error : Failed to initialize the points!\n");
    }

}

void Polygon::draw(){
    printf("Drawing the polygon with %d vertices\n", numVertices);
    fflush(stdout);
    
    int i = 0;
    while (i < numVertices - 1 ) {
        canvas->drawLine(vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i+1].y, color); // Draws a line on the canvas
        i++;
    }
    canvas->drawLine(vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, color); // Draws a line on the canvas
}

void Polygon::clear(){
    printf("Drawing the polygon with %d vertices\n", numVertices);
    int i = 0;
    while (i < numVertices - 1 ) {
        canvas->drawLine(vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i+1].y, canvas->getBackgroundColor()); // Draws a line on the canvas
        i++;
    }
    canvas->drawLine(vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, canvas->getBackgroundColor()); // Draws a line on the canvas

    free(vertices);
}

void Polygon::drawBuffer(){
    printf("Drawing the polygon with %d vertices\n", numVertices);
    int i = 0;
    while (i < numVertices - 1 ) {
        canvas->drawLineBuffer(vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i+1].y, color); // Draws a line on the canvas
        i++;
    }
    canvas->drawLineBuffer(vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, color); // Draws a line on the canvas               
}

void Polygon::clearBuffer(){
    printf("Drawing the polygon with %d vertices\n", numVertices);
    int i = 0;
    while (i < numVertices - 1 ) {
        canvas->drawLineBuffer(vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i+1].y, transparent); // Draws a line on the canvas
        i++;
    }
    canvas->drawLineBuffer(vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, transparent); // Draws a line on the canvas               
}

