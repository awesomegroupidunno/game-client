#ifndef GAME_CLIENT_ENCODEDECODE_H
#define GAME_CLIENT_ENCODEDECODE_H


class EncodeDecode
{
public:
	virtual const char* encode(char *command) = 0;
	virtual char* decode(char* buffer) = 0;
};


#endif //GAME_CLIENT_ENCODEDECODE_H
