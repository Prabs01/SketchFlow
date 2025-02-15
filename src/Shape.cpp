
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