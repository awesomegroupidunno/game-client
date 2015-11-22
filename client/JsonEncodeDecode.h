#ifndef GAME_CLIENT_JSONENCODEDECODE_H
#define GAME_CLIENT_JSONENCODEDECODE_H

#include <iostream>
#include <stdio.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/error/en.h"
#include "EncodeDecode.h"

using namespace rapidjson;

class JsonEncodeDecode : public EncodeDecode
{
private:
	int decodeVehicle(GameState* state, const Value& vehicle);
	int decodeBullet(GameState* state, const Value& bullet);
	int decodeBase(GameState* state, const Value& base);
	int decodeShield(GameState* state, const Value& shield);
	int decodeShieldGen(GameState* state, const Value& shield_gen);
	int decodePowerup(GameState* state, const Value& powerup);

public:
	const char* encode(Command* c, int mode);
	GameState* decode(const char *buffer);
};

#endif //GAME_CLIENT_JSONENCODEDECODE_H
