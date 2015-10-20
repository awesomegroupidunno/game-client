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
	GameState* state = new GameState;

	// Iterate through JSON document
	for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
	{
		// Grab the updated Vehicles
		if (itr->name.GetString() == "Vehicles")
		{
			// Iterate through Vehicle array
			const Value& array = itr->value;
			for (SizeType i = 0; i < array.Size(); i++)
			{
				if (decodeVehicle(state, array[i]) == 0)
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
	int x = NULL, y = NULL, velocity = NULL, angle = NULL, endurance = NULL;

	// Iterate through JSON vehicle object
	const char* check;
	for (Value::ConstMemberIterator itr = vehicle.MemberBegin(); itr != vehicle.MemberEnd(); ++itr)
	{
		check = itr->name.GetString();

		if (strcmp(check, "X"))
		{
			x = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Y"))
		{
			y = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Velocity"))
		{
			velocity = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Angle"))
		{
			angle = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Endurance"))
		{
			endurance = itr->value.GetInt();
			continue;
		}
	}

	// Error checking
	if (x == NULL || y == NULL || velocity == NULL || angle == NULL || endurance == NULL)
	{
		// Return error value
		return 0;
	}

	// Create a new Vehicle
	Vehicle* new_vehicle = new Vehicle(x, y, endurance, angle, velocity);

	// Push it to the GameState
	state->addPlayer(new_vehicle);

	return 1;
}