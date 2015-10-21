//
// Created by austin4e on 10/10/15.
//

#ifndef GAME_CLIENT_SDLINPUTADAPTER_H
#define GAME_CLIENT_SDLINPUTADAPTER_H

#include <set>
#include "SDL2/SDL.h"
#include "GameController.h"

class SdlInputAdapter
{
private:
	GameController* gameController;
	std::set<SDL_Keycode>* keys;

public:
	SdlInputAdapter(GameController* gc);

	void check_keys();
	void key_down(SDL_Event event);
	void key_up(SDL_Event event);
};


#endif //GAME_CLIENT_SDLINPUTADAPTER_H
