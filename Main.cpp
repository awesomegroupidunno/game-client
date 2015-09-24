#include <iostream>
#include <SDL2/SDL.h>

int SDLTest();

int main()
{
    // TODO: The following is an idea of how Main.cpp should look
    // Draw window / game screen
    // Initialize ServerModel.json
    // Initialize game loop / GameController.cpp
    // Handle exiting game

    SDLTest();

    return 0;
}

int SDLTest()
{
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Hello Car Combat!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Set renderer to window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create rect
    SDL_Rect rect;
    rect.x = 50;
    rect.y = 50;
    rect.w = 50;
    rect.h = 50;

    // A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
    for (int i = 0; i < 3; ++i)
    {
        // Make background white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        // First clear the renderer
        SDL_RenderClear(renderer);

        // Rect color
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

        // Draw rect
        SDL_RenderFillRect(renderer, &rect);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Take a quick break after all that hard work
        SDL_Delay(1000);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}