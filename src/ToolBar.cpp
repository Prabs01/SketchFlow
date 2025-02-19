#include"ToolBar.h"



ToolBar::ToolBar(){cout<<endl;}

ToolBar::ToolBar(int SW, int SH){
    bgcolor = lightGray;
    activeTool = nullptr;
    area = {0,0,100,SH};
    SDL_Rect TOOLBAR_RECT = {0,0,100,SH};
    tools.push_back(new Pencil);
    tools.push_back(new Eraser);
    tools.push_back(new Filler);
    tools.push_back(new LineDrawer);
    tools.push_back(new SelectTool);
    initColorBoxes();
}

void ToolBar::setRenderer(SDL_Renderer* renderer_){
    renderer = renderer_;
    for(int i = 0 ;i<tools.size();i++){
        tools[i]->makeTexture(renderer);
    }
}

void ToolBar::setToolCanvas(Canvas* canvas_){   //main -> toolbar -> tool (give canvas permission)
    canvas = canvas_;
    for(int i = 0 ;i<tools.size();i++){
        tools[i]->setCanvas(canvas_);
    }
}

void ToolBar::initColorBoxes() {
    int boxSize = 50;
    int startX = 0;
    int startY = 500; // Adjust this value based on the position of the tools
    int padding = 5;

    // Define 15 solid colors
    std::vector<Color> colors = {
        Color(255, 0, 0), Color(0, 255, 0), Color(0, 0, 255),
        Color(255, 255, 0), Color(0, 255, 255), Color(255, 0, 255),
        Color(192, 192, 192), Color(128, 128, 128), Color(0, 128, 0),
        Color(128, 0, 128), Color(128, 128, 0), Color(0, 128, 128),
        Color(0, 0, 128), Color(128, 0, 0), Color(255, 165, 0)
    };

    for (int i = 0; i < 16; ++i) {
        SDL_Rect rect = {startX + (i % 2) * (boxSize + padding), startY + (i / 2) * (boxSize + padding), boxSize, boxSize};
        Color color = (i < 15) ? colors[i] : Color(255, 255, 255); // Last box is empty (white)
        colorBoxes.push_back({rect, color});
    }

    currentColor = colors[0]; // Default drawing color
}

void ToolBar::renderColorBoxes() {
    for (const auto& box : colorBoxes) {
        SDL_SetRenderDrawColor(renderer, box.color.r, box.color.g, box.color.b, 255);
        SDL_RenderFillRect(renderer, &box.rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &box.rect);

        if (box.color.toUint32() == currentColor.toUint32()) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Set the draw color to blue for the border
            SDL_RenderDrawRect(renderer, &box.rect); // Render the border again to make it bold
        }
    }
}

void ToolBar::renderCurrentColorBox(SDL_Renderer* renderer, Color currentColor) {
    SDL_Rect colorBox = { 10, 60, 50, 50 }; // Define the position and size of the current color box
    SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a); // Set the draw color to the current color
    SDL_RenderFillRect(renderer, &colorBox); // Render the filled rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set the draw color to black for the border
    SDL_RenderDrawRect(renderer, &colorBox); // Render the border
}

void ToolBar::render(){     //renders the toolbar with all the shapes/tools and also hover-click effect
    SDL_SetRenderDrawColor(renderer, bgcolor.r,bgcolor.g,bgcolor.b,bgcolor.a);
    SDL_RenderFillRect(renderer, &area);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    for(int i = 0; i<tools.size();i++){
        tools[i]->render();
        tools[i]->hover();
    }

    if(activeTool){
        activeTool->drawCursor(); //draws the active tool cursor on the canvas
        activeTool->clicked();  //makes dark after tool is selected
    }

    renderColorBoxes(); // Render color boxes
    
}

bool ToolBar::mouseClicked(SDL_Event& event){
    int mouseX = event.motion.x;
    int mouseY = event.motion.y;
    

    for (auto& colorBox : colorBoxes) {
        if (mouseX >= colorBox.rect.x && mouseX <= colorBox.rect.x + colorBox.rect.w &&
            mouseY >= colorBox.rect.y && mouseY <= colorBox.rect.y + colorBox.rect.h) {
            currentColor = colorBox.color;
            activeTool->setToolColor(currentColor);
            return true;
        }
    }

    if(mouseX >= area.x && mouseX <=(area.x + area.w) && mouseY >=area.y && mouseY<=(area.y+area.h)){
        
        for(int i = 0; i<tools.size();i++){
            if(tools[i]->isMouseOver()){
                
                if(activeTool)
                    activeTool->unSelect();
                    
                activeTool = tools[i];

                // if(activeTool){
                //     printf(" tool%d set ",i);
                //     fflush(stdout);
                // }
            }
        }
        return true;
    }
    else{
        return false;
    }
}

void ToolBar::handleEvent(SDL_Event& event){ //tool event handler : handles the active tool functionality
    if(activeTool){
        if(event.type == SDL_MOUSEBUTTONUP){
            activeTool -> onMouseUp(event);
        }else if(event.type == SDL_MOUSEBUTTONDOWN){
            if (event.button.button == SDL_BUTTON_LEFT){
                mouseClicked(event);
            }
            activeTool -> onMouseDown(event);
        }else if(event.type == SDL_MOUSEMOTION){
            activeTool -> onMouseMove(event);
        }else if(event.type == SDL_KEYDOWN){
            activeTool -> keyboardInput(event);
        }
    }
}

Color ToolBar::getCurrentColor() const {
    return currentColor;
}

bool ToolBar::isColorButtonClicked(int x, int y) {
    for (const auto& colorBox : colorBoxes) {
        if (x >= colorBox.rect.x && x <= colorBox.rect.x + colorBox.rect.w &&
            y >= colorBox.rect.y && y <= colorBox.rect.y + colorBox.rect.h) {
            return true;
        }
    }
    return false;
}

Color ToolBar::getSelectedColor() {
    return currentColor;
}


ToolBar::~ToolBar(){
    for (auto tool : tools) {
        free(tool);
    }
}