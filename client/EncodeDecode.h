#ifndef GAME_CLIENT_ENCODEDECODE_H
#define GAME_CLIENT_ENCODEDECODE_H

struct Command
{
	char const* type;
	char const* subtype;
	int value;
};

class EncodeDecode
{
public:
	virtual const char* encode(Command* c) = 0;
	virtual char* decode(char* buffer) = 0;
};


#endif //GAME_CLIENT_ENCODEDECODE_H
