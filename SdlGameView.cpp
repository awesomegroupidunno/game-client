//
// Created by austin4e on 9/26/15.
//
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "SdlGameViewAdapter.h"

class SdlGameView{
    // Init SDL
public:
    int drawView() {
        if (SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        // Create window
        SDL_Window *window = SDL_CreateWindow("Hello Car Combat!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        // Set renderer to window
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            SDL_DestroyWindow(window);
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        //TODO: THIS IS FOR TESTING DRAWING VEHICLES
        SdlGameViewAdapter gva;
        int numCars = gva.getVehicles().size();
        printf("%i\n", numCars);
        SDL_Rect* cars = new SDL_Rect[numCars];

        // TODO: HELP FIX THIS, CARS AREN'T BEING GRABBED FROM GAMESTATE PROPERLY
        // Take the vehicles from the vehicle vector
        // Use their values to begin drawing
        printf("SETTING CARS FROM VEHICLE VECTOR\n");
        for (int i = 0; i < numCars; i++){
            cars[i].x = gva.getVehicles().at(i)->x;
            cars[i].y = gva.getVehicles().at(i)->y;
            cars[i].w = 50;
            cars[i].h = 50;
        }

        SDL_Rect test;
        test.x = 50;
        test.y = 50;
        test.w = 50;
        test.h = 50;

        // A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
        for (int i = 0; i < 3; ++i) {
                // Make background white
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                // First clear the renderer
                SDL_RenderClear(renderer);
            for (int j = 0; j < numCars; j++) {
                printf("ATTEMPTING TO DRAW VEHICLE\n");
                // Rect color
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                // Draw rect
                SDL_RenderFillRect(renderer, &cars[j]);
            }
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
                SDL_RenderFillRect(renderer, &cars[0]);
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
};