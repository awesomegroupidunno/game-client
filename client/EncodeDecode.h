#ifndef GAME_CLIENT_ENCODEDECODE_H
#define GAME_CLIENT_ENCODEDECODE_H

#include "Command.h"

class EncodeDecode
{
public:
	virtual const char* encode(Command* c, int mode) = 0;
	virtual char* decode(char* buffer) = 0;
};


#endif //GAME_CLIENT_ENCODEDECODE_H
