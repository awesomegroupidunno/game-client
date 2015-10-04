#include "JsonEncodeDecode.h"

const char* JsonEncodeDecode::encode(char *command)
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.String("Command");
	writer.String(command);
	writer.EndObject();

	return s.GetString();
}

char* JsonEncodeDecode::decode(char* buffer)
{
	JsonHandler handler;
	Reader reader;
	StringStream ss(buffer);
	reader.Parse(ss, handler);

	return buffer;
}