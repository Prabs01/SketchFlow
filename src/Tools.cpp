#include "Tools.h"


//the bound box and images of the tool icons in the tool bar
SDL_Rect PENCIL_RECT = {0,0, 100,100};
char PENCIL_IMAGE_URL[] = "../resources/pencil.png";

SDL_Rect ERASER_RECT = {0,100, 100,100};
char ERASER_IMAGE_URL[] = "../resources/eraser.png";


SDL_Rect FILLER_RECT = {0,200,100,100};
char FILLER_IMAGE_URL[] = "../resources/paint.png";

SDL_Rect LINE_DRAWER_RECT = {0,300,50,50};
char LINE_DRAWER_IMAGE_URL[] = "../resources/line.png";

SDL_Rect SELECT_TOOL_RECT = {0,400,100,100};
char SELECT_TOOL_IMAGE_URL[] = "../resources/select.png";

SDL_Rect POLYGON_TOOL_RECT = {50, 300, 50, 50 };
char POLYGON_TOOL_IMAGE_URL[] = "../resources/polygon.png";

SDL_Rect RECTANGLE_TOOL_RECT = {0, 350, 50, 50 };
char RECTANGLE_TOOL_IMAGE_URL[] = "../resources/rectangle.png";

SDL_Rect ELLIPSE_TOOL_RECT = {50, 350, 50, 50 };
// char ELLIPSE_TOOL_IMAGE_URL[] = "../resources/ellipse.png";

void Tools::setCanvas(Canvas* canvas_){
    canvas = canvas_;
}

bool Tools::isMouseOver(){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if(mouseX >= bound_box.x && mouseX <=(bound_box.x + bound_box.w) && mouseY>=bound_box.y && mouseY<=(bound_box.y+bound_box.h)){
        return true;
    }else{
        return false;
    }
}

void Tools::hover(){
    if(isMouseOver()){
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, gray.r,gray.g,gray.b,100);
        SDL_RenderFillRect(renderer, &bound_box);
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    }
}

void Tools::clicked(){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, black.r,black.g,black.b,100);
    SDL_RenderFillRect(renderer, &bound_box);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}

void Tools::setToolColor(Color color){
    toolColor = color;
}



/*############################### Pencil #############################*/
#pragma region
Pencil::Pencil(){
    pixelSize = 5;
    bound_box = PENCIL_RECT;
    isDrawing = false;
    lastPos.x = -100;
    lastPos.y = -100;
    toolColor = black;
}

void Pencil::makeTexture(SDL_Renderer* renderer_){
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer,PENCIL_IMAGE_URL);
    if(!imgTexture){
        printf("failes to load the pencil image texture %s \n",SDL_GetError());
    }
}   

void Pencil::render(){
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);
    // SDL_SetRenderDrawColor(renderer, 0, 255,255,0);
    // SDL_RenderFillRect(renderer,&bound_box);
    // SDL_SetRenderDrawColor(renderer, 0, 0,0,0);
}

void Pencil::onMouseDown(SDL_Event& event){
    if(!isDrawing){
        canvas->pushCanvas();
    }
    isDrawing = true;
    lastPos.x = event.motion.x;
    lastPos.y = event.motion.y;
}

void Pencil::onMouseUp(SDL_Event& event){
    if(isDrawing){
        isDrawing = false;
        lastPos.x = -100;
        lastPos.y = -100;
    }
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

void Pencil::setPixelSize(int pixelSize_){
    pixelSize = pixelSize_;
}

void Pencil::drawCursor() {
    // int x, y;
    // SDL_GetMouseState(&x, &y);
    // if (canvas->isInside(x, y)) {
    //     SDL_ShowCursor(SDL_DISABLE);
    //     canvas->clearBuffer();
    //     canvas->drawLineBuffer(x, y, x + 10, y - 10, black); // Simple pencil symbol (diagonal line)
    // } else {
    //     SDL_ShowCursor(SDL_ENABLE);
    //     canvas->clearBuffer();
    // }
}

void Pencil::unSelect(){

}
#pragma endregion

/*############################### Eraser #############################*/
#pragma region  
Eraser::Eraser(){
    eraserSize = 20;
    bound_box = ERASER_RECT;
    isDrawing = false;
    lastPos.x = -100;
    lastPos.y = -100;
    toolColor = white;
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
        canvas->drawLineBuffer(x,y,x+eraserSize,y,black);
        canvas->drawLineBuffer(x,y,x,y+eraserSize, black);
        canvas->drawLineBuffer(x+eraserSize,y,x+eraserSize,y+eraserSize,black);
        canvas->drawLineBuffer(x,y+eraserSize,x+eraserSize,y+eraserSize,black);
    }else{
        SDL_ShowCursor(SDL_ENABLE);
        canvas->clearBuffer();
    }
}

void Eraser::onMouseDown(SDL_Event& event){
    if(!isDrawing){
        canvas->pushCanvas();
    }
    isDrawing = true;
    lastPos.x = event.motion.x;
    lastPos.y = event.motion.y;
}

void Eraser::onMouseUp(SDL_Event& event){
    if(isDrawing){
        isDrawing = false;
        lastPos.x = -100;
        lastPos.y = -100;
    }
    
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

void Eraser::unSelect(){
    
}
#pragma endregion

/*###############################Filler Tool #############################*/
#pragma region
Filler::Filler(){
    toolColor = red;
    current_color = white;
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
        canvas->pushCanvas();
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


void Filler::keyboardInput(SDL_Event& event){
    if(event.key.keysym.sym == SDLK_EQUALS){

    }else if(event.key.keysym.sym == SDLK_MINUS){

    }
}

void Filler::fill(int EP1, int EP2){
  
    if (!canvas->isInside(EP1,EP2)) return;
    if (toolColor.toUint32() == current_color.toUint32()) return;
    if (canvas->getPixelColor(EP1, EP2).toUint32() == toolColor.toUint32()) return;

    vector<int> xp,yp;
    xp.push_back(EP1);
    yp.push_back(EP2);

    while (!xp.empty()) {

        int x = xp.back();xp.pop_back();
        int y = yp.back();yp.pop_back();

        if (!canvas->isInside(x,y)) continue;
        if (canvas->getPixelColor(x, y).toUint32() != current_color.toUint32()) continue;

        canvas->setPixel(x, y, toolColor);

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

void Filler::setBoundaryColor(Color color){
    boundary_color = color;
}

void Filler::drawCursor(){
    
}

void Filler::unSelect(){
    
}

#pragma endregion

/*###############################Select Tool #############################*/
#pragma region
SelectTool::SelectTool(){
    clipRect = {-1,-1,0,0};
    bool isSelected = false;
    bool isSelecting = false;

    lastMousePos = {-1,-1};

    bound_box = SELECT_TOOL_RECT;

    clipRectColor = brown;
}

void SelectTool::makeTexture(SDL_Renderer* renderer_){
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer,SELECT_TOOL_IMAGE_URL);
    if(!imgTexture){
        printf("failes to load the select tool image texture %s \n",SDL_GetError());
    }
}

void SelectTool::render(){
    SDL_RenderDrawRect(renderer, &bound_box);
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);

    drawClipRect();
}

void SelectTool::onMouseDown(SDL_Event& event){

    //this is the intial state
    if(!isSelecting && !isSelected){
        canvas->pushCanvas();
        isSelecting = true; // goto selecting state
        int x = event.motion.x;
        int y = event.motion.y;
        clipRect.x = x;
        clipRect.y = y;
    }

    //state when the portion is selected
    if(!isSelecting && isSelected){
        if(isCursorInside()){
            isSelecting = true; //goto moving state
            isSelected = true;
            lastMousePos = {event.motion.x,event.motion.y}; // needed to calculate dx and dy for moving
    
        }else{
            isSelecting = false; //goto the initial state
            isSelected = false;
            clearClipRect();
           
            canvas->copyToCanvas(clipRect); //copy content of buffer to canvas and clear the buffer
            canvas->clearBuffer(clipRect);

            clipRect = {-1,-1,0,0};

        }
    }

    //state when portion is being moved
    if(isSelecting && isSelected){
        if(!isCursorInside()){
            isSelecting = false; // go to the initial state
            isSelected = false;
            clearClipRect();

            canvas->copyToCanvas(clipRect); //copy content of buffer to canvas and clear the buffer
            canvas->clearBuffer(clipRect);
            clipRect = {-1,-1,0,0};


        }
    }

}

void SelectTool::onMouseUp(SDL_Event& event){
    //state when the portion is being selected
    if(isSelecting && !isSelected){
        isSelecting = false; //go to the selected state
        isSelected = true;

        canvas->copyToBuffer(clipRect); // copy the content of canvas to buffer and clear the canvas
        canvas->clear(clipRect);

    }


    //state when portion is being moved
    if(isSelecting && isSelected){
        isSelecting = false; //go to the selected state
        isSelected = true;
    }
}

void SelectTool::onMouseMove(SDL_Event& event){
    //state when the potion is being selected
    if(isSelecting && !isSelected){
        int x = event.motion.x;
        int y = event.motion.y;

        clearClipRect();//we need to clear the previous cliprect before drawing other

        clipRect.w = x - clipRect.x;
        clipRect.h = y - clipRect.y;
    }

    //state when the portion is being moved
    if(isSelecting && isSelected && canvas->isInside(clipRect)){
        int x = event.motion.x;
        int y = event.motion.y;

        if(lastMousePos.x == -1 && lastMousePos.y == -1){
            lastMousePos = {x,y};
        }

        int dx = (x - lastMousePos.x);
        int dy = (y- lastMousePos.y);

        clearClipRect();

        SDL_Rect buffer = clipRect;

        buffer.x = clipRect.x + dx;
        buffer.y = clipRect.y + dy;

        if(canvas -> isInside(buffer)){
            
            canvas->moveBufferContent(dx, dy, clipRect);// move the content as the mouse moves
            clipRect = buffer;
        }
        lastMousePos = {x,y};
    }
}

void SelectTool::keyboardInput(SDL_Event& event){

}

void SelectTool::drawCursor() {
    static int prevX = -1, prevY = -1;
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (canvas->isInside(x, y) && !isSelected) {
        SDL_ShowCursor(SDL_DISABLE);
        if (prevX != -1 && prevY != -1) {
            canvas->clearLineBuffer(prevX - 5, prevY, prevX + 5, prevY); // Clear previous cursor position
            canvas->clearLineBuffer(prevX, prevY - 5, prevX, prevY + 5);
        }
        canvas->drawLineBuffer(x - 5, y, x + 5, y, black); // Horizontal line of +
        canvas->drawLineBuffer(x, y - 5, x, y + 5, black); // Vertical line of +
        prevX = x;
        prevY = y;
    } else {
        SDL_ShowCursor(SDL_ENABLE);
        canvas->clearLineBuffer(prevX - 5, prevY, prevX + 5, prevY); // Clear previous cursor position
        canvas->clearLineBuffer(prevX, prevY - 5, prevX, prevY + 5);
        prevX = prevY = -1;
    }
}

void SelectTool::drawClipRect(){
    canvas->drawLineBuffer(clipRect.x, clipRect.y, clipRect.x + clipRect.w, clipRect.y, clipRectColor);
    canvas->drawLineBuffer(clipRect.x+clipRect.w, clipRect.y, clipRect.x + clipRect.w, clipRect.y+ clipRect.h, clipRectColor);
    canvas->drawLineBuffer(clipRect.x, clipRect.y + clipRect.h, clipRect.x + clipRect.w, clipRect.y+ clipRect.h, clipRectColor);
    canvas->drawLineBuffer(clipRect.x, clipRect.y, clipRect.x, clipRect.y+ clipRect.h, clipRectColor);
}
void SelectTool::clearClipRect(){
    canvas->clearLineBuffer(clipRect.x, clipRect.y, clipRect.x + clipRect.w, clipRect.y);
    canvas->clearLineBuffer(clipRect.x+clipRect.w, clipRect.y, clipRect.x + clipRect.w, clipRect.y+ clipRect.h);
    canvas->clearLineBuffer(clipRect.x, clipRect.y + clipRect.h, clipRect.x + clipRect.w, clipRect.y+ clipRect.h);
    canvas->clearLineBuffer(clipRect.x, clipRect.y, clipRect.x, clipRect.y+ clipRect.h);
}

bool SelectTool::isCursorInside(){
    int x,y;
    SDL_GetMouseState(&x,&y);

    SDL_Rect rect = clipRect;
    if (rect.w < 0) {
        rect.x += rect.w;
        rect.w = -rect.w;
    }
    if (rect.h < 0) {
        rect.y += rect.h;
        rect.h = -rect.h;
    }
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

void SelectTool::unSelect(){
    canvas->copyToCanvas(clipRect); //copy content of buffer to canvas and clear the buffer
    canvas->clearBuffer();
    clipRect = {-1,-1,0,0};

    printf("unselect called");
    fflush(stdout);
}

#pragma endregion

/*###############################Line Drawing Tool #############################*/
#pragma region 
LineDrawer::LineDrawer(){
    startingPixel = {-100,-100};
    endingPixel = {-100,-100};
    width = 3;
    toolColor = black;
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
        canvas->pushCanvas();

        startingPixel.x = x;
        startingPixel.y  = y;
        endingPixel.x = x;
        endingPixel.y = y;
        drawing = true;
        drawingLine = Line(startingPixel, endingPixel, width, toolColor);
        drawingLine.setCanvas(canvas);
    }
}

void LineDrawer::onMouseMove(SDL_Event& event){
    int x = event.motion.x;
    int y = event.motion.y;

    
    if(drawing){
        // canvas->clearLineBuffer(startingPixel.x, startingPixel.y, endingPixel.x,endingPixel.y);
        drawingLine.clearBuffer();
        drawingLine.setEndingPoint(x,y);
    //    printf("helloo3\n");
    //     fflush(stdout);
        drawingLine.drawBuffer();
    }
    

}

void LineDrawer::onMouseUp(SDL_Event& event){
    if(drawing){
        drawingLine.draw();
        drawing = false;
        drawingLine.clearBuffer();
    }
    
}


void LineDrawer::keyboardInput(SDL_Event& event){
    if(event.key.keysym.sym == SDLK_EQUALS){
        width += 1;
    }else if(event.key.keysym.sym == SDLK_MINUS){
        if(width >=2)
        width -= 1;
    }
}

void LineDrawer::drawCursor(){
    
}

void LineDrawer::unSelect(){
    
}

#pragma endregion

/*###############################Polygon Tool #############################*/
#pragma region
// Constructor
PolygonTool::PolygonTool(int numVertices){
    center = {-100,-100};
    vertex = {-100,-100};
    noVertices = numVertices;
    width = 3;
    toolColor = black;
    isDrawing = false;
    bound_box = POLYGON_TOOL_RECT; // Set the bounding box for the tool icon
    polygon = Polygon(numVertices, -10,-10,-10,-10);
}

// Load the polygon icon
void PolygonTool::makeTexture(SDL_Renderer* renderer_) {
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer, POLYGON_TOOL_IMAGE_URL);
    if (!imgTexture) {
        printf("Failed to load polygon image texture: %s\n", SDL_GetError());
    }
}

// Render the tool icon
void PolygonTool::render() {
    SDL_RenderDrawRect(renderer, &bound_box);
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);
}

// Handle mouse down event
void PolygonTool::onMouseDown(SDL_Event& event) {
    int x = event.motion.x;
    int y = event.motion.y;

    if(!isDrawing && !isMoving){
        canvas->pushCanvas();

        center.x = x;
        center.y  = y;
        vertex.x = x;
        vertex.y = y;
        isDrawing = true;
        polygon = Polygon(noVertices, center.x, center.y, vertex.x, vertex.y, width, toolColor);
        polygon.setCanvas(canvas);

        printf("\nstate 2");
        fflush(stdout);
    }
    if(!isDrawing && isMoving){
        if(polygon.isPointInside(x,y)){
            isMoving = true;
            isDrawing = true;
            prevX = x;
            prevY = y;

            printf("\nstate 4");
            fflush(stdout);
        }
    }

    if(isMoving){
        if(!polygon.isPointInside(x,y)){
            isMoving = false;
            isDrawing = false;

            polygon.clearBuffer();
            polygon.draw();

            printf("\nstate 1");
            fflush(stdout);
        }
    }

}

// Handle mouse move event
void PolygonTool::onMouseMove(SDL_Event& event) {  
    int x = event.motion.x;
    int y = event.motion.y;

    
    if(isDrawing && !isMoving){
        // canvas->clearLineBuffer(startingPixel.x, startingPixel.y, endingPixel.x,endingPixel.y);
        polygon.clearBuffer();
        polygon.setEndingPoint(x,y);
    //    printf("\nhelloo3\n");
    //     fflush(stdout);
        polygon.drawBuffer();
    }
    
    if(isDrawing && isMoving){
        // Calculate movement offset
        int dx = x - prevX;
        int dy = y - prevY;

        polygon.clearBuffer();
        // Move the polygon
        polygon.move(dx, dy);

        polygon.drawBuffer();

        // Update previous position
        prevX = x;
        prevY = y;
    }
}

// Handle mouse up event
void PolygonTool::onMouseUp(SDL_Event& event) {
    if (isDrawing && !isMoving) {

        isDrawing = false; // Stop drawing
        isMoving = true;

        printf("state 3");
        fflush(stdout);

    }

    if(isDrawing && isMoving){
        isDrawing = false;
        isMoving = true;

        printf("state 3");
        fflush(stdout);
    }
}

// Draw the cursor for the tool
void PolygonTool::drawCursor() {
}

// Handle keyboard input (if needed)
void PolygonTool::keyboardInput(SDL_Event& event) {
    if(event.key.keysym.sym == SDLK_EQUALS){
        width += 1;
    }else if(event.key.keysym.sym == SDLK_MINUS){
        if(width >=2)
        width -= 1;
    }

    if(event.key.keysym.sym == SDLK_3){
        noVertices = 3;
    }else if(event.key.keysym.sym == SDLK_4){
        noVertices = 4;
    }else if(event.key.keysym.sym == SDLK_5){
        noVertices = 5;
    }else if(event.key.keysym.sym == SDLK_6){
        noVertices = 6;
    }else if(event.key.keysym.sym == SDLK_7){
        noVertices = 7;
    }else if(event.key.keysym.sym == SDLK_8){
        noVertices = 8;
    }else if(event.key.keysym.sym == SDLK_9){
        noVertices = 9;
    }else if(event.key.keysym.sym == SDLK_1){
        noVertices+=1;
    }else if(event.key.keysym.sym == SDLK_0){
        noVertices -=1 ;
    }
}

// Reset the tool state
void PolygonTool::unSelect() {
    // canvas->clearBuffer(); // Clear the buffer
    // polygon.clear(); // Clear points
    // isDrawing = false; // Reset drawing state
}

#pragma endregion


/*###############################Rectangle Tool #############################*/
#pragma region
// Constructor
RectTool::RectTool(){
    vertex1 = {-100,-100};
    vertex2 = {-100,-100};
    width = 3;
    toolColor = black;
    isDrawing = false;
    isMoving = false;
    bound_box = RECTANGLE_TOOL_RECT; // Set the bounding box for the tool icon
    rectangle = Rectangle();
}

// Load the polygon icon
void RectTool::makeTexture(SDL_Renderer* renderer_) {
    renderer = renderer_;
    imgTexture = IMG_LoadTexture(renderer, RECTANGLE_TOOL_IMAGE_URL);
    if (!imgTexture) {
        printf("Failed to load polygon image texture: %s\n", SDL_GetError());
    }
}

// Render the tool icon
void RectTool::render() {
    SDL_RenderDrawRect(renderer, &bound_box);
    SDL_RenderCopy(renderer, imgTexture, NULL, &bound_box);
}

void RectTool::onMouseDown(SDL_Event& event) {
    int x = event.motion.x;
    int y = event.motion.y;

    if(!isDrawing && !isMoving){
        canvas->pushCanvas();
        
        vertex1.x = x;
        vertex1.y  = y;
        vertex2.x = x;
        vertex2.y = y;
        isDrawing = true;
        rectangle = Rectangle( vertex1.x, vertex1.y, vertex2.x, vertex2.y, width, toolColor);
        rectangle.setCanvas(canvas);
    }

    if(!isDrawing && isMoving){
        if(rectangle.isPointInside(x,y)){
            isMoving = true;
            isDrawing = true;
            prevX = x;
            prevY = y;

            printf("\nstate 4");
            fflush(stdout);
        }
    }

    if(isMoving){
        if(!rectangle.isPointInside(x,y)){
            isMoving = false;
            isDrawing = false;

            rectangle.clearBuffer();
            rectangle.draw();

            printf("\nstate 1");
            fflush(stdout);
        }
    }
}

void RectTool::onMouseMove(SDL_Event& event) {  
    int x = event.motion.x;
    int y = event.motion.y;
   
    if(isDrawing && !isMoving){
        // canvas->clearLineBuffer(startingPixel.x, startingPixel.y, endingPixel.x,endingPixel.y);
        rectangle.clearBuffer();
        rectangle.setEndingPoint(x,y);
    //    printf("\nhelloo3\n");
    //     fflush(stdout);
        rectangle.drawBuffer();
    }
    
    if(isDrawing && isMoving){
        // Calculate movement offset
        int dx = x - prevX;
        int dy = y - prevY;

        rectangle.clearBuffer();
        // Move the rectangle
        rectangle.move(dx, dy);

        rectangle.drawBuffer();

        // Update previous position
        prevX = x;
        prevY = y;
    }
}

// Handle mouse up event
void RectTool::onMouseUp(SDL_Event& event) {
    if (isDrawing && !isMoving) {

        isDrawing = false; // Stop drawing
        isMoving = true;

        printf("state 3");
        fflush(stdout);

    }

    if(isDrawing && isMoving){
        isDrawing = false;
        isMoving = true;

        printf("state 3");
        fflush(stdout);
    }
}

// Draw the cursor for the tool
void RectTool::drawCursor() {
}

// Handle keyboard input (if needed)
void RectTool::keyboardInput(SDL_Event& event) {
    if(event.key.keysym.sym == SDLK_EQUALS){
        width += 1;
    }else if(event.key.keysym.sym == SDLK_MINUS){
        if(width >=2)
        width -= 1;
    }
    if(event.key.keysym.sym == SDLK_r){
        if(isDrawing || isMoving){
            double angle = (M_PI / 180.0)*5;  // M_PI is a constant in <cmath>
            rectangle.clearBuffer();
            rectangle.rotate(angle);
            rectangle.drawBuffer();
        }
    }
    if(event.key.keysym.sym == SDLK_e){
        if(isDrawing || isMoving){
            double angle = -(M_PI / 180.0)*5;  // M_PI is a constant in <cmath>
            rectangle.clearBuffer();
            rectangle.rotate(angle);
            rectangle.drawBuffer();
        }
    }
}

// Reset the tool state
void RectTool::unSelect() {
    // canvas->clearBuffer(); // Clear the buffer
    // polygon.clear(); // Clear points
    // isDrawing = false; // Reset drawing state
}

#pragma endregion