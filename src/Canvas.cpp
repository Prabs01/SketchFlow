#include"Canvas.h"

SDL_Rect CANVAS_RECT = {0,0,0,0};

Canvas::Canvas(){
    area = {100,0,700-100,500};
    CANVAS_RECT ={100,0,700-100,500};
    pixels = new Uint32[area.w * area.h];
    bufferPixels = new Uint32[area.w * area.h];
    showBuffer = true;
    bgColor = white;
    clear();
    clearBuffer();
}
Canvas::Canvas(int SW,int SH){
    area = {100,0,SW-100,SH};
    CANVAS_RECT ={100,0,SW-100,SH};
    pixels = new Uint32[area.w * area.h];
    bufferPixels = new Uint32[area.w * area.h];
    showBuffer = true;
    bgColor = white;
    clear();
    clearBuffer();
}

void Canvas::init(SDL_Renderer* renderer_){
    renderer = renderer_;
    canvasTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STATIC, area.w, area.h);
    SDL_SetTextureBlendMode(canvasTexture, SDL_BLENDMODE_BLEND);

    bufferTexture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STATIC, area.w, area.h);
    SDL_SetTextureBlendMode(bufferTexture, SDL_BLENDMODE_BLEND);
}
void Canvas::updatePixels(){
    SDL_UpdateTexture(canvasTexture, NULL, pixels,area.w * sizeof(Uint32));
}

void Canvas::updateBuffer(){
    SDL_UpdateTexture(bufferTexture, NULL, bufferPixels,area.w * sizeof(Uint32));
}

void Canvas::render(){  //after updating the pixels, render it to the screen
    SDL_RenderCopy(renderer, canvasTexture, NULL, &area);
    if(showBuffer){
        SDL_RenderCopy(renderer,bufferTexture,NULL, &area);
    }
    
}

//canvas cooords & canvas size : relative to window
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
    if(x >= area.x && x<=(area.w+100) && y>=0 && y<=area.h){
        return true;
    }else{
        return false;
    }
}

bool Canvas::isInside(SDL_Rect rect){   // for rectangles like select tool
    return(isInside(rect.x,rect.y) && isInside(rect.x+rect.w, rect.y)
     && isInside(rect.x,rect.y+rect.h) && isInside(rect.x+rect.w, rect.y+rect.h));
}

void Canvas::fitCanvas(int* x, int* y){ //sends points out of canvas to inside canvas - for mouse
    *x =*x + area.x;
    *y =*y + area.y;
}

void Canvas::absoluteCord(int* x, int* y){  // canvas coordinate to window coordinate
    *x = *x - area.x;
    *y = *y - area.y;
}

void Canvas::setPixel(int x, int y, Color color){
    if(x >= area.x && x<=area.w + area.x && y>=area.y && y<=area.h+area.y){
        x = x-area.x;
        y = y-area.y;
        pixels[y*area.w + x] = color.toUint32();
    }
}

void Canvas::setPixelBuffer(int x, int y, Color color){
    if(x >= area.x && x<=area.w + area.x && y>=area.y && y<=area.h+area.y){
        x = x-area.x;
        y = y-area.y;
        bufferPixels[y*area.w + x] = color.toUint32();
    }
}

Color Canvas::getPixelColor(int x, int y){
    x = x - area.x;
    y = y - area.y;
    
    Uint32 pixel = pixels[y * area.w + x];

    Uint8 r = (pixel >> 16) & 0xFF;  // Extract red (8 bits)
    Uint8 g = (pixel >> 8) & 0xFF;   // Extract green (8 bits)
    Uint8 b = pixel & 0xFF;          // Extract blue (8 bits)
    Uint8 a = (pixel >> 24) & 0xFF;  // Extract alpha (8 bits)

    // Return the Color object with extracted RGBA values
    return Color(r, g, b, a);
}

Color Canvas::getPixelColorBuffer(int x, int y){
    x = x - area.x;
    y = y - area.y;
    
    Uint32 pixel = bufferPixels[y * area.w + x];

    // Extract the individual RGBA components from the pixel value
    Uint8 r = (pixel >> 16) & 0xFF;  // Extract red (8 bits)
    Uint8 g = (pixel >> 8) & 0xFF;   // Extract green (8 bits)
    Uint8 b = pixel & 0xFF;          // Extract blue (8 bits)
    Uint8 a = (pixel >> 24) & 0xFF;  // Extract alpha (8 bits)

    // Return the Color object with extracted RGBA values
    return Color(r, g, b, a);
}

Color Canvas::getBackgroundColor(){
    return bgColor;
}

void Canvas::clear(SDL_Rect portion){
    for(int i = portion.x +1; i<portion.x+ portion.w;i++){
        for(int j = portion.y+1; j<portion.y + portion.h;j++){
            int x = i, y = j;
            // fitCanvas(&x,&y);
            setPixel(x,y,white);
        }
    }
}
void Canvas::clearBuffer(SDL_Rect portion){
    for(int i = portion.x +1 ; i<portion.x+ portion.w;i++){
        for(int j = portion.y+1; j<portion.y + portion.h;j++){
            int x = i, y = j;
            // fitCanvas(&x,&y);
            setPixelBuffer(x,y,transparent);
        }
    }
}


Canvas::~Canvas(){
    delete[] pixels;
    SDL_DestroyTexture(canvasTexture);
}


void Canvas::drawLine(int x1, int y1, int x2, int y2,Color color){
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int ix = (x1<x2)?1:-1;
    int iy = (y1<y2)?1:-1;

    int x = x1;
    int y = y1;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){
            setPixel(x,y, color); 
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
            setPixel(x,y, color); 
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

void Canvas::drawLineBuffer(int x1, int y1, int x2, int y2, Color color){
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int ix = (x1<x2)?1:-1;
    int iy = (y1<y2)?1:-1;

    int x = x1;
    int y = y1;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){
            setPixelBuffer(x,y, color); 
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
            setPixelBuffer(x,y, color); 
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
            setPixel(x,y, bgColor); 
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
            setPixel(x,y, bgColor); 
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

void Canvas::clearLineBuffer(int x1, int y1, int x2, int y2){
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int ix = (x1<x2)?1:-1;
    int iy = (y1<y2)?1:-1;

    int x = x1;
    int y = y1;

    if(dx>dy){
        int p = 2*dy - dx;
        for(int i = 0; i < dx; i++){
            setPixelBuffer(x,y,transparent); 
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
            setPixelBuffer(x,y, transparent); 
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

void Canvas::viewBuffer(){
    showBuffer = true;
    //clearBuffer();
}

void Canvas::removeBuffer(){
    showBuffer = false;
    //clearBuffer();
}

void Canvas::copyToBuffer(SDL_Rect copyArea){
    for(int i = copyArea.x + 1; i<copyArea.x + copyArea.w;i++){
        for(int j = copyArea.y + 1; j<copyArea.y + copyArea.h;j++){

            int x = i;
            int y = j;

            x = x- area.x; // we need to transform the copy area co-ordinates to canvas co-ordinates
            y = y-area.y;

            if(pixels[y*area.w + x] != bgColor.toUint32())
                bufferPixels[y*area.w +x] = pixels[y*area.w + x];
                // printf("coping to buffer");
                // fflush(stdout);
        }
    }
}

void Canvas::copyToCanvas(SDL_Rect copyArea){
   for(int i = copyArea.x + 1 ; i<copyArea.x + copyArea.w;i++){
        for(int j = copyArea.y + 1; j<copyArea.y + copyArea.h;j++){

            int x = i;
            int y = j;

            x = x- area.x; // we need to transform the copy area co-ordinates to canvas co-ordinates
            y = y-area.y;

            if(bufferPixels[y*area.w + x] != transparent.toUint32())
                pixels[y*area.w +x] = bufferPixels[y*area.w + x];
        }
    }
}

void Canvas::moveBufferContent(int dx, int dy,SDL_Rect moveArea){
    Uint32* temp;
    temp = new Uint32[area.w * area.h];

    //The content for the moveArea in the buffer is swapped with the new moveArea content and previous area is cleared

    for(int i = moveArea.x + 1; i<moveArea.x+ moveArea.w;i++){
        for(int j = moveArea.y + 1; j<moveArea.y + moveArea.h;j++){
            int x = i, y=j;
            if(isInside(x, y)){
                x = i - area.x;
                y = j - area.y;
                // fitCanvas(&x,&y);
                temp[j*area.w + i] = bufferPixels[y*area.w + x];
            }
        }
    }

    for(int i = moveArea.x +1; i<moveArea.x+ moveArea.w;i++){
        for(int j = moveArea.y + 1; j<moveArea.y + moveArea.h;j++){
            int x = i, y=j;
            if(isInside(x, y)){
                x = i - area.x;
                y = j - area.y;
                bufferPixels[y*area.w + x] = transparent.toUint32();
            }
            
        }
    }

    for(int i = moveArea.x +1; i<moveArea.x + moveArea.w;i++){
        for(int j = moveArea.y +1; j<moveArea.y + moveArea.h;j++){
            int newx = i + dx;
            int newy = j + dy;
            if(isInside(newx, newy)){
                newx =newx - area.x;
                newy = newy - area.y;
                if(temp[j*area.w + i] != bgColor.toUint32()){
                    bufferPixels[newy*area.w +newx] = temp[j*area.w + i];
                }
            }
        }
    }

}

void Canvas::pushCanvas(){
    Uint32* snapShot = new Uint32[area.w * area.h];
    memcpy(snapShot, pixels,area.w*area.h*sizeof(Uint32));
    undoStack.push(snapShot);

    printf("\npushed");
    fflush(stdout);
}

void Canvas::popCanvas() {
    if (undoStack.empty()) {  
        printf("\nUndo stack is empty!");
        fflush(stdout);
        return;
    }

    Uint32* lastState = undoStack.top();
    undoStack.pop();

    if (!lastState) {  
        printf("\nError: Last state is a nullptr!");
        fflush(stdout);
        return;
    }

    if (!pixels) {  
        printf("\nError: pixels is NULL! Cannot restore.");
        fflush(stdout);
        delete[] lastState;
        return;
    }

    memcpy(pixels, lastState, area.w * area.h * sizeof(Uint32));

    delete[] lastState;

    printf("\nUndo performed successfully.");
    fflush(stdout);
}

