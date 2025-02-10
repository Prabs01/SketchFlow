#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#elif __APPLE__
    #include <SDL.h>
    #include <SDL_image.h>
#else
    #include <SDL2/SDL.h>  // Linux (also works for other Unix-like systems)
    #include <SDL2/SDL_image.h>
#endif

#include <iostream>

#include "Canvas.h"
#include "ToolBar.h"
#include "Shape.h"

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
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                lastMouseX = lastMouseY = -1; // Reset last position
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    leftMouseButtonDown = true;
                    toolBar.mouseClicked(event);
                }
                break;

            case SDL_MOUSEMOTION:
                
                break;
        }

       //canvas.drawLine(100,100,400,500);
        
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

