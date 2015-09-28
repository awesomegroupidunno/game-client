//
// Created by austin4e on 9/26/15.
//
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "SdlGameViewAdapter.h"

class SdlGameView{
private:
	SDL_Renderer *renderer;
	const int carWidth = 50;
	const int carHeight = 75;

public:
	void drawVehicle(SDL_Rect* vehicle) {
		// Rect color
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		// Draw rect
		SDL_RenderFillRect(renderer, vehicle);
	}

    int drawView() {
		// Init SDL
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
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            SDL_DestroyWindow(window);
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        //TODO: THIS IS FOR TESTING DRAWING VEHICLES
        SdlGameViewAdapter gva;
        int numCars = gva.getVehicles().size();
        printf("number of cars = %i\n", numCars);
        SDL_Rect* cars = new SDL_Rect[numCars];
        // Take the vehicles from the vehicle vector
        // Use their values to begin drawing
        printf("SETTING CARS FROM VEHICLE VECTOR\n");
        for (int i = 0; i < numCars; i++){
            cars[i].x = gva.getVehicles().at(i)->x;
            cars[i].y = gva.getVehicles().at(i)->y;
            cars[i].w = carWidth;
            cars[i].h = carHeight;
        }

        // A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
		bool gameRunning = true;
		int tick = 0;
        while (gameRunning) {

			// Listen for the exit
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}

			// Make background white
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			// First clear the renderer
			SDL_RenderClear(renderer);

			printf("DRAWING: tick %i\n", tick);

			for (int j = 0; j < numCars; j++) {
				drawVehicle(&cars[j]);
			}

			// Update the screen
			SDL_RenderPresent(renderer);

			// Take a quick break after all that hard work
			SDL_Delay(40);

			// Next tick
			tick++;
        }

        // Clean up
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    }
};