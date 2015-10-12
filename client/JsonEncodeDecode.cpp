#include "JsonEncodeDecode.h"

const char* JsonEncodeDecode::encode(Command* c)
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();

	writer.String("Type");
	writer.String(c->type);
	writer.String("Subtype");
	writer.String(c->subtype);
	if (c->numValue != NULL)
	{
		writer.String("Value");
		writer.Int(c->numValue);
	}
	if (c->strValue != NULL)
	{
		writer.String("Value");
		writer.String(c->strValue);
	}

	writer.EndObject();

	return s.GetString();
}

char* JsonEncodeDecode::decode(char* buffer)
{
	Document doc;

	// Parse and catch errors
	if (doc.Parse(buffer).HasParseError())
	{
		printf("\n----------\nError (offset %u): %s\n----------\n",
				(unsigned)doc.GetErrorOffset(),
				GetParseError_En(doc.GetParseError()));
		return NULL;
	}

	// Currently just print out all types in received message
	int pos = 0;
	static const char* typeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
	{
		pos += sprintf(&buffer[pos], "Type of member %s is %s\n", itr->name.GetString(), typeNames[itr->value.GetType()]);
	}

	return buffer;
}