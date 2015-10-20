#ifndef GAME_CLIENT_ENCODEDECODE_H
#define GAME_CLIENT_ENCODEDECODE_H

#include "Command.h"

// TODO: fix CMakeLists so we don't need to do file path stuff in includes!
#include "../GameState.h"

class EncodeDecode
{
public:
	virtual const char* encode(Command* c, int mode) = 0;
	virtual GameState* decode(char* buffer) = 0;
};


#endif //GAME_CLIENT_ENCODEDECODE_H
