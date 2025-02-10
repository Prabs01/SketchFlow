#include "Tools.h"

SDL_Rect PENCIL_RECT = {0,0, 100,100};
char PENCIL_IMAGE_URL[] = "C:/Users/Satyam/Desktop/paint/SketchFlow/resources/paint.jpg";

SDL_Rect ERASER_RECT = {0,100, 100,100};
char ERASER_IMAGE_URL[] = "C:/Users/Satyam/Desktop/paint/SketchFlow/resources/eraser.png";


SDL_Rect FILLER_RECT = {0,200,100,100};
char FILLER_IMAGE_URL[] = "C:/Users/Satyam/Desktop/paint/SketchFlow/resources/paint.jpg";

SDL_Rect LINE_DRAWER_RECT = {0,300,50,50};
char LINE_DRAWER_IMAGE_URL[] = "C:/Users/Satyam/Desktop/paint/SketchFlow/resources/line.png";

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

void Pencil::keyboardInput(SDL_Event& event){
    if(event.key.keysym.sym == SDLK_EQUALS){
        pixelSize += 1;
    }else if(event.key.keysym.sym == SDLK_MINUS && pixelSize >1){
        pixelSize -= 1;
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

void Pencil::drawCursor(){

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
    
    
}

void Eraser::drawCursor(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    if(canvas->isInside(x,y)){
        SDL_ShowCursor(SDL_DISABLE);
        canvas->clearBuffer();
        canvas->drawLineBuffer(x,y,x+eraserSize,y);
        canvas->drawLineBuffer(x,y,x,y+eraserSize);
        canvas->drawLineBuffer(x+eraserSize,y,x+eraserSize,y+eraserSize);
        canvas->drawLineBuffer(x,y+eraserSize,x+eraserSize,y+eraserSize);
    }else{
        SDL_ShowCursor(SDL_ENABLE);
        canvas->clearBuffer();
    }
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

void Eraser::keyboardInput(SDL_Event& event){
    if(event.key.keysym.sym == SDLK_EQUALS){
        eraserSize += 1;
    }else if(event.key.keysym.sym == SDLK_MINUS && eraserSize >5){
        eraserSize -= 1;
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

void Filler::keyboardInput(SDL_Event& event){
    if(event.key.keysym.sym == SDLK_EQUALS){

    }else if(event.key.keysym.sym == SDLK_MINUS){

    }
}

void Filler::fill(int EP1, int EP2){
  
    if (!canvas->isInside(EP1,EP2)) return;
    if (fill_color == current_color) return;
    if (canvas->getPixelColor(EP1, EP2) == fill_color) return;

    vector<int> xp,yp;
    xp.push_back(EP1);
    yp.push_back(EP2);

    while (!xp.empty()) {

        int x = xp.back();xp.pop_back();
        int y = yp.back();yp.pop_back();

        if (!canvas->isInside(x,y)) continue;
        if (canvas->getPixelColor(x, y) != current_color) continue;

        canvas->setPixel(x, y, fill_color);

        xp.push_back(x - 1);yp.push_back(y);
        xp.push_back(x + 1);yp.push_back(y);
        xp.push_back(x);yp.push_back(y-1);
        xp.push_back(x );yp.push_back(y+1);
        xp.push_back(x - 1);yp.push_back(y-1);
        xp.push_back(x + 1);yp.push_back(y+1);
        xp.push_back(x+1);yp.push_back(y-1);
        xp.push_back(x-1);yp.push_back(y+1);

    }
    
}

void Filler::setColor(Uint32 color){
    fill_color = color;
}

void Filler::setBoundaryColor(Uint32 color){
    boundary_color = color;
}

void Filler::drawCursor(){
    
}



LineDrawer::LineDrawer(){
    startingPixel = {-100,-100};
    endingPixel = {-100,-100};
    width = 5;
    color = 0x00000000;
    drawing = false;
    bound_box = LINE_DRAWER_RECT;
}

void LineDrawer::makeTexture(SDL_Renderer* renderer_){
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer,LINE_DRAWER_IMAGE_URL);
    if(!imgTexture){
        printf("failes to load the pencil image texture %s \n",SDL_GetError());
    }
}

void LineDrawer::render(){
    SDL_RenderDrawRect(renderer, &bound_box);
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);
}

void LineDrawer::onMouseDown(SDL_Event& event){
    int x = event.motion.x;
    int y = event.motion.y;

    if(!drawing){
        startingPixel.x = x;
        startingPixel.y  = y;
        endingPixel.x = x;
        endingPixel.y = y;
        drawing = true;
    }
}

void LineDrawer::onMouseMove(SDL_Event& event){
    int x = event.motion.x;
    int y = event.motion.y;

    
    if(drawing){
        canvas->clearLineBuffer(startingPixel.x, startingPixel.y, endingPixel.x,endingPixel.y);
        endingPixel.x = x;
        endingPixel.y = y;
        canvas->drawLineBuffer(startingPixel.x, startingPixel.y, endingPixel.x,endingPixel.y);
    }
    

}

void LineDrawer::onMouseUp(SDL_Event& event){
    if(drawing){
        canvas->drawLine(startingPixel.x,startingPixel.y,endingPixel.x,endingPixel.y);
        drawing = false;
        canvas->clearBuffer();
    }
    
}

bool LineDrawer::isMouseOver(){
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

void LineDrawer::keyboardInput(SDL_Event& event){
    if(event.key.keysym.sym == SDLK_EQUALS){
        width += 1;
    }else if(event.key.keysym.sym == SDLK_MINUS){
        width -= 1;
    }
}

void LineDrawer::drawCursor(){
    
}

