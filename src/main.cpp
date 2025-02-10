
#include<SDL.h>
#include<iostream>
#include<SDL_image.h>

#include"Canvas.h"
#include"ToolBar.h"
#include"Shape.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;



int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT,0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Canvas canvas;
    ToolBar toolBar;

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

