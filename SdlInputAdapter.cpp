//
// Created by austin4e on 10/10/15.
//

#include "SdlInputAdapter.h"

SdlInputAdapter::SdlInputAdapter(GameController* gc){
    gameController = gc;
}
// Listens for input from user, responds with calls to GameController
void SdlInputAdapter::inputListener(SDL_Event event){
            SDL_Keycode keyPressed = event.key.keysym.sym;
            switch (keyPressed) {
                // ARROW KEYS
                case SDLK_UP:
                    // handle forward motion
                    gameController->moveVehicle(1);
                    printf("input up\n");
                    break;
                case SDLK_DOWN:
                    // handle reverse motion
                    gameController->moveVehicle(-1);
                    printf("input down\n");
                    break;
                case SDLK_LEFT:
                    // handle turning left
                    gameController->turnVehicle(1);
                    printf("input left\n");
                    break;
                case SDLK_RIGHT:
                    // handle turning right
                    gameController->turnVehicle(-1);
                    printf("input right\n");
                    break;
            }
}
