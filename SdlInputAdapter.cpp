//
// Created by austin4e on 10/10/15.
//

#include "SdlInputAdapter.h"

SdlInputAdapter::SdlInputAdapter(GameController* gc)
{
	gameController = gc;
	keys = new std::set<SDL_Keycode>();
}

void SdlInputAdapter::check_keys()
{
	for (std::set<SDL_Keycode>::iterator itr = keys->begin(); itr != keys->end(); ++itr)
	{
		switch (*itr)
		{
			// ARROW KEYS
			case SDLK_UP:
				// handle forward motion
				printf("input up\n");
				gameController->moveVehicle(1.0);
				break;
			case SDLK_DOWN:
				// handle reverse motion
				printf("input down\n");
				gameController->moveVehicle(-1.0);
				break;
			case SDLK_LEFT:
				// handle turning left
				printf("input left\n");
				gameController->turnVehicle(1.0);
				break;
			case SDLK_RIGHT:
				// handle turning right
				printf("input right\n");
				gameController->turnVehicle(-1.0);
				break;
			case SDLK_SPACE:
				// handle firing weapon
				printf("input fire\n");
				gameController->fireWeapon();
				break;

			// Any other keys
			default:
				// Ignore
				break;
		}
	}
}

// Responds to a key down event
void SdlInputAdapter::key_down(SDL_Event event)
{
	SDL_Keycode keyPressed = event.key.keysym.sym;
	keys->insert(keyPressed);
}

// Responds to a key up event
void SdlInputAdapter::key_up(SDL_Event event)
{
	SDL_Keycode keyPressed = event.key.keysym.sym;
	keys->erase(keyPressed);
}
