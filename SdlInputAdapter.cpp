//
// Created by austin4e on 10/10/15.
//

#include "SdlInputAdapter.h"

SdlInputAdapter::SdlInputAdapter(GameController* gc){
    gameController = gc;
}
// Listens for input from user, responds with calls to GameController
void SdlInputAdapter::inputListener(SDL_Event event){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode keyPressed = event.key.keysym.sym;
            switch (keyPressed) {
                // ARROW KEYS
                case SDLK_UP:
                    // handle forward motion
                    gameController->moveVehicle(1);
                case SDLK_DOWN:
                    // handle reverse motion
                    gameController->moveVehicle(-1);
                case SDLK_LEFT:
                    // handle turning left
                    gameController->turnVehicle(1);
                case SDLK_RIGHT:
                    // handle turning right
                    gameController->turnVehicle(-1);
            }
        }
    }
}
