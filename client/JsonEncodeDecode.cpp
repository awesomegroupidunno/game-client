#include "JsonEncodeDecode.h"

const char* JsonEncodeDecode::encode(Command* c, int mode)
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();

	writer.String("Type");
	writer.String(c->type);
	writer.String("Subtype");
	writer.String(c->subtype);
	if (mode == NUM_MODE)
	{
		writer.String("Value");
		writer.Int(c->numValue);
	}
	if (mode == STRING_MODE)
	{
		writer.String("Value");
		writer.String(c->strValue);
	}

	writer.EndObject();

	return s.GetString();
}

GameState* JsonEncodeDecode::decode(char* buffer)
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

	// Create new GameState
	GameState* state = new GameState();

	// Iterate through JSON document
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
	{
		// Grab the updated Vehicles
		if (strcmp(itr->name.GetString(), "Vehicles") == 0)
		{
			// If Vehicles is not an array, something went wrong
			if (!itr->value.IsArray())
			{
				printf("\n----------\nError: Vehicles array is not array\n----------\n");
				return NULL;
			}

			// Iterate through Vehicle array
			const Value& array = itr->value;
			for (SizeType i = 0; i < array.Size(); i++)
			{
				if (decodeVehicle(state, array[i]) == -1)
				{
					printf("\n----------\nError decoding vehicles\n----------\n");
					return NULL;
				}
			}
		}
	}

	return state;
}

int JsonEncodeDecode::decodeVehicle(GameState* state, const Value& vehicle)
{
	// Vehicle vars
	int x = 0, y = 0, velocity = 0, angle = 0, endurance = 0;

	// Iterate through JSON vehicle object
	const char* check;
	for (Value::ConstMemberIterator itr = vehicle.MemberBegin(); itr != vehicle.MemberEnd(); ++itr)
	{
		check = itr->name.GetString();

		if (strcmp(check, "X") == 0)
		{
			x = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Y") == 0)
		{
			y = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Velocity") == 0)
		{
			velocity = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Angle") == 0)
		{
			angle = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Endurance") == 0)
		{
			endurance = itr->value.GetInt();
			continue;
		}
	}

	// Create a new Vehicle
	Vehicle* new_vehicle = new Vehicle(x, y, endurance, angle, velocity);

	// Push it to the GameState
	state->addPlayer(new_vehicle);

	return 1;
}