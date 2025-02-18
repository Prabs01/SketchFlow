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

    
}

bool ToolBar::mouseClicked(SDL_Event& event){
    int mouseX = event.motion.x;
    int mouseY = event.motion.y;
    

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

ToolBar::~ToolBar(){
}