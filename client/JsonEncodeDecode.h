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
public:
	const char* encode(Command* c);
	char* decode(char* buffer);
};

#endif //GAME_CLIENT_JSONENCODEDECODE_H
