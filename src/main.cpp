#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }


    SDL_Rect displayBounds;
    if (SDL_GetDisplayBounds(0, &displayBounds) != 0) {
        std::cerr << "Failed to get display bounds: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow(
        "Hello SDL",                    // Window title
        SDL_WINDOWPOS_UNDEFINED,        // Initial X position
        SDL_WINDOWPOS_UNDEFINED,        // Initial Y position
        displayBounds.w,                            // Width
        displayBounds.h,                            // Height
        SDL_WINDOW_SHOWN                // Flags
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create a renderer to draw on the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Event loop to keep the window open
    bool running = true;
    SDL_Event event;

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int newWidth = event.window.data1;
                    int newHeight = event.window.data2;
                    std::cout << "Window resized to " << newWidth << "x" << newHeight << std::endl;

                    // You can use the new size to update your rendering viewport if needed
                    SDL_RenderSetLogicalSize(renderer, newWidth, newHeight);
                }
            }
    }
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
