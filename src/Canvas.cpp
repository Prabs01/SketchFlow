#include"Canvas.h"

SDL_Rect CANVAS_RECT = {100,10,700,500};
Canvas::Canvas(){
    area = CANVAS_RECT;
    pixels = new Uint32[area.w * area.h];
    clear();
}

void Canvas::init(SDL_Renderer* renderer_){
    renderer = renderer_;

    canvaTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STATIC, area.w, area.h);
}
void Canvas::updatePixels(){
    SDL_UpdateTexture(canvaTexture, NULL, pixels,area.w * sizeof(Uint32));
}

void Canvas::render(){
    SDL_RenderCopy(renderer, canvaTexture,NULL, &area);
}

int Canvas::getXmax(){
    return area.x+area.w;
}
int Canvas::getXmin(){
    return area.x;
}

int Canvas::getYmax(){
    return area.y+area.h;
}

int Canvas::getYmin(){
    return area.y;
}

bool Canvas::isInside(int x, int y){
    if(x >= area.x && x<=area.w + area.x && y>=area.y && y<=area.h+area.y){
        return true;
    }else{
        return false;
    }
}

void Canvas::fitCanvas(int* x, int* y){
    *x -= area.x;
    *y -= area.y;
}

void Canvas::setPixel(int x, int y, Uint32 color){
    if(x >= area.x && x<=area.w + area.x && y>=area.y && y<=area.h+area.y){
        x = x-area.x;
        y = y-area.y;
        pixels[y*area.w + x] = color;
    }
}

Uint32 Canvas::getPixelColor(int x, int y){
    x = x-area.x;
    y = y-area.y;
    return pixels[y*area.w +x];
}

void Canvas::clear(){
    memset(pixels, 255, area.w*area.h*sizeof(Uint32));
}

Canvas::~Canvas(){
    delete[] pixels;
    SDL_DestroyTexture(canvaTexture);
}


void Canvas::drawLine(int x1, int y1, int x2, int y2){
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int ix = (x1<x2)?1:-1;
    int iy = (y1<y2)?1:-1;

    int x = x1;
    int y = y1;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){
            setPixel(x,y, 0X00000000); 
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
            setPixel(x,y, 0X00000000); 
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

void Canvas::clearLine(int x1, int y1, int x2, int y2){
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int ix = (x1<x2)?1:-1;
    int iy = (y1<y2)?1:-1;

    int x = x1;
    int y = y1;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){
            setPixel(x,y, 0XFFFFFFFF); 
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
            setPixel(x,y, 0XFFFFFFFF); 
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