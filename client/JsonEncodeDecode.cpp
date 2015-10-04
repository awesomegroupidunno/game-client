#include <stdio.h>
#include "JsonEncodeDecode.h"

const char* JsonEncodeDecode::encode(char* command)
{
	/*StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.String("Command");
	writer.String(command);
	writer.EndObject();

	return s.GetString();*/

	return (const char*) command;
}

char* JsonEncodeDecode::decode(char* buffer)
{
	Document doc;
	doc.Parse(buffer);

	int pos = 0;
	static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
	{
		pos += sprintf(&buffer[pos], "Type of member %s is %s\n", itr->name.GetString(), kTypeNames[itr->value.GetType()]);
	}

	return buffer;
}