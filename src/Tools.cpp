#include "Tools.h"

SDL_Rect PENCIL_RECT = {0,0, 100,100};
char PENCIL_IMAGE_URL[] = "../resources/pencil.png";

SDL_Rect ERASER_RECT = {0,100, 100,100};
char ERASER_IMAGE_URL[] = "../resources/eraser.png";


SDL_Rect FILLER_RECT = {0,200,100,100};
char FILLER_IMAGE_URL[] = "../resources/paint.jpg";

void Tools::setCanvas(Canvas* canvas_){
    canvas = canvas_;
}



//Functions of pencil

Pencil::Pencil(){
    pixelSize = 5;
    bound_box = PENCIL_RECT;
    isDrawing = false;
    lastPos.x = -100;
    lastPos.y = -100;
}

void Pencil::makeTexture(SDL_Renderer* renderer_){
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer,PENCIL_IMAGE_URL);
    if(!imgTexture){
        printf("failes to load the pencil image texture %s \n",SDL_GetError());
    }
}   

void Pencil::render(){
    SDL_RenderDrawRect(renderer, &bound_box);
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);
}

void Pencil::onMouseDown(SDL_Event& event){
    isDrawing = true;
    lastPos.x = event.motion.x;
    lastPos.y = event.motion.y;
}

void Pencil::onMouseUp(SDL_Event& event){
    isDrawing = false;
    lastPos.x = -100;
    lastPos.y = -100;
}

void Pencil::onMouseMove(SDL_Event& event){
    if(isDrawing){
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        // If this is the first motion event, initialize last position
        if (lastPos.x == -100 && lastPos.y == -100) {
            lastPos.x = mouseX;
            lastPos.y = mouseY;
        }

        // Interpolate between last position and current position
        int dx = mouseX - lastPos.x;
        int dy = mouseY - lastPos.y;
        int steps = max(abs(dx), abs(dy)); // Number of interpolation steps

        for (int i = 0; i <= steps; i++) {
            float t = (float)i / steps;
            int interpX = lastPos.x + t * dx;
            int interpY = lastPos.y + t * dy;

            // Draw the "big pixel" directly
            for (int y = 0; y < pixelSize; ++y) {
                for (int x = 0; x < pixelSize; ++x) {
                    int pixelX = interpX + x;
                    int pixelY = interpY + y;

                    canvas->setPixel(pixelX, pixelY, toolColor);
                }
            }
        }
        lastPos.x = mouseX;
        lastPos.y = mouseY;
    }
    
}

bool Pencil::isMouseOver(){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if(mouseX >= bound_box.x && mouseX <=(bound_box.x + bound_box.w) && mouseY>=bound_box.y && mouseY<=(bound_box.y+bound_box.h)){
        // printf(" Pencil selected ");
        // fflush(stdout);
        return true;
    }else{
        return false;
    }
}

void Pencil::setPixelSize(int pixelSize_){
    pixelSize = pixelSize_;
}

void Pencil::setColor(Uint32 color){
    toolColor = color;
}




//functions for eraser
Eraser::Eraser(){
    eraserSize = 20;
    bound_box = ERASER_RECT;
    isDrawing = false;
    lastPos.x = -100;
    lastPos.y = -100;
    toolColor = 0xFFFFFFFF;
    eraserRect = {100,100, eraserSize, eraserSize};
}

void Eraser::makeTexture(SDL_Renderer* renderer_){
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer,ERASER_IMAGE_URL);
    if(!imgTexture){
        printf("failes to load the Eraser image texture %s \n",SDL_GetError());
    }
}   

void Eraser::render(){
    SDL_RenderDrawRect(renderer, &bound_box);
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    // eraserRect.x = mouseX;
    // eraserRect.y = mouseY;
    // eraserRect.w = eraserSize;
    // eraserRect.h = eraserSize;
    // canvas->drawLine(eraserRect.x,eraserRect.y,eraserRect.x+eraserRect.w,eraserRect.y);
}

void Eraser::onMouseDown(SDL_Event& event){
    isDrawing = true;
    lastPos.x = event.motion.x;
    lastPos.y = event.motion.y;
}

void Eraser::onMouseUp(SDL_Event& event){
    isDrawing = false;
    lastPos.x = -100;
    lastPos.y = -100;
}

void Eraser::onMouseMove(SDL_Event& event){
    if(isDrawing){
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        // If this is the first motion event, initialize last position
        if (lastPos.x == -100 && lastPos.y == -100) {
            lastPos.x = mouseX;
            lastPos.y = mouseY;
        }

        // Interpolate between last position and current position
        int dx = mouseX - lastPos.x;
        int dy = mouseY - lastPos.y;
        int steps = max(abs(dx), abs(dy)); // Number of interpolation steps

        for (int i = 0; i <= steps; i++) {
            float t = (float)i / steps;
            int interpX = lastPos.x + t * dx;
            int interpY = lastPos.y + t * dy;

            // Draw the "big pixel" directly
            for (int y = 0; y < eraserSize; ++y) {
                for (int x = 0; x < eraserSize; ++x) {
                    int pixelX = interpX + x;
                    int pixelY = interpY + y;

                    canvas->setPixel(pixelX, pixelY, toolColor);
                }
            }
        }
        lastPos.x = mouseX;
        lastPos.y = mouseY;
    }
    
}

bool Eraser::isMouseOver(){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if(mouseX >= bound_box.x && mouseX <=(bound_box.x + bound_box.w) && mouseY>=bound_box.y && mouseY<=(bound_box.y+bound_box.h)){
        // printf(" Eraser selected ");
        // fflush(stdout);
        return true;
        
    }else{
        return false;
    }
}

void Eraser::setEraserSize(int eraserSize_){
    eraserSize = eraserSize_;
}

void Eraser::setColor(Uint32 color){
    toolColor = color;
}


// Filler

Filler::Filler(){
    fill_color = 0xFFFF0000;
    current_color = 0xFFFFFFFF;
    bound_box = FILLER_RECT;
    pixelSelected = false;
}


void Filler::makeTexture(SDL_Renderer* renderer_){
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer,FILLER_IMAGE_URL);
    if(!imgTexture){
        printf("failes to load the Filler image texture %s \n",SDL_GetError());
    }
}

void Filler::render(){
    SDL_RenderDrawRect(renderer, &bound_box);
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);
}

void Filler::onMouseUp(SDL_Event& event){
    pixelSelected = false;
}

void Filler::onMouseDown(SDL_Event& event){
    if(!pixelSelected){
        int x = event.motion.x;
        int y = event.motion.y;
        current_color = canvas->getPixelColor(x,y);

        fill(x,y);
        pixelSelected = true;
    }
}

void Filler::onMouseMove(SDL_Event& event){
    return;
}

bool Filler::isMouseOver(){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if(mouseX >= bound_box.x && mouseX <=(bound_box.x + bound_box.w) && mouseY>=bound_box.y && mouseY<=(bound_box.y+bound_box.h)){
        // printf(" Eraser selected ");
        // fflush(stdout);
        return true;
        
    }else{
        return false;
    }
}


void Filler::fill(int x, int y){
    Uint32 pixelColor = canvas -> getPixelColor(x, y);

    if(!canvas ->isInside(x,y)){
        return;
    }

    if(pixelColor != fill_color && pixelColor == current_color){
            canvas -> setPixel(x,y, fill_color);
            fill(x-1, y);
            fill(x+1,y);
            fill(x,y-1);
            fill(x,y+1);
    }
    else{
        return;
    }
}

void Filler::setColor(Uint32 color){
    fill_color = color;
}

void Filler::setBoundaryColor(Uint32 color){
    boundary_color = color;
}