#include<SDL.h>
#include<iostream>
#include<SDL_image.h>

#include"Canvas.h"
#include"ToolBar.h"
#include"Shape.h"
using namespace std;

//SDL_DisplayMode displayMode;

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);   // Mode of operation .i.e video mode
    SDL_Init(IMG_INIT_PNG);     // which file to handle i.e png
    

    SDL_DisplayMode displayMode;
    int displayIndex = 0; // Primary display
    
    if (SDL_GetCurrentDisplayMode(displayIndex, &displayMode) != 0) {
        std::cerr << "SDL_GetCurrentDisplayMode Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    int SCREEN_WIDTH = displayMode.w;
    int SCREEN_HEIGHT = displayMode.h;


   
    SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing", 0, 25, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);


    Canvas canvas(SCREEN_WIDTH,SCREEN_HEIGHT);
    ToolBar toolBar(SCREEN_WIDTH,SCREEN_HEIGHT);


    canvas.init(renderer);
    toolBar.setRenderer(renderer);
    toolBar.setToolCanvas(&canvas);


    bool quit = false;
    SDL_Event event;


    SDL_Init(SDL_INIT_VIDEO);

    bool leftMouseButtonDown = false;

    int PIXEL_SIZE = 1; //only for testing purpose
    int lastMouseX = -1, lastMouseY = -1; // Track the last mouse position



    //for select tool test
    SDL_Rect clipRect = {-100,-100,0,0};
    bool isSelecting = false;
    //////

    while (!quit) {
        //SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
        canvas.updatePixels();
        canvas.updateBuffer();

        SDL_WaitEvent(&event);

        toolBar.handleEvent(event);

        switch (event.type) {

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SCREEN_WIDTH = event.window.data1;
                    SCREEN_HEIGHT = event.window.data2;
                    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                break;
           
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_c)
                    canvas.clear();

                //temp
                if(event.key.keysym.sym == SDLK_UP)
                    // line.move(0,-5);

                if(event.key.keysym.sym == SDLK_LEFT)
                    // line.move(-5,0);

                if(event.key.keysym.sym == SDLK_RIGHT)
                    // line.move(5,0);

                if(event.key.keysym.sym == SDLK_DOWN)
                    // line.move(0,5);


            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    //test
                    isSelecting = false;
                    clipRect = {-100,-100,0,0};
                }
                    
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    toolBar.mouseClicked(event);

                    //test
                    if(!isSelecting){
                        isSelecting = true;
                        int x = event.motion.x;
                        int y = event.motion.y;
                        clipRect.x = x;
                        clipRect.y = y;
                    }
                    ////////////
                }
                break;

            case SDL_MOUSEMOTION:
                //test
                if(isSelecting){
                    int x = event.motion.x;
                    int y = event.motion.y;
                    clipRect.w = x - clipRect.x;
                    clipRect.h = y - clipRect.y;
                }
                ///////
                
                break;
        }

       //canvas.drawLine(100,100,400,500);

       //for select tool test
       if(isSelecting){
            canvas.clearBuffer();
            canvas.drawLineBuffer(clipRect.x, clipRect.y, clipRect.x + clipRect.w, clipRect.y, brown);
            canvas.drawLineBuffer(clipRect.x+clipRect.w, clipRect.y, clipRect.x + clipRect.w, clipRect.y+ clipRect.h, brown);
            canvas.drawLineBuffer(clipRect.x, clipRect.y + clipRect.h, clipRect.x + clipRect.w, clipRect.y+ clipRect.h, brown);
            canvas.drawLineBuffer(clipRect.x, clipRect.y, clipRect.x, clipRect.y+ clipRect.h, brown);
       }

        
        SDL_RenderClear(renderer);

        toolBar.render();
        canvas.render();
    
        SDL_RenderPresent(renderer);
    }      

    // delete[] pixels;
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

