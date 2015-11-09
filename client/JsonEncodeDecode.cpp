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
		writer.Double(c->numValue);
	}
	if (mode == STRING_MODE)
	{
		writer.String("Value");
		writer.String(c->strValue);
	}

	writer.EndObject();
	size_t len = 1 + strlen(s.GetString()) * (sizeof(char));
	char *str = (char*)malloc(len);
	str = strcpy(str, s.GetString());
	str[len-1] = '\0';
	return str;
}

GameState* JsonEncodeDecode::decode(const char *buffer)
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
		/*
		 * VEHICLES
		 */
		if (strcmp(itr->name.GetString(), "Vehicles") == 0)
		{
			// If Vehicles is not an array, something went wrong
			if (!itr->value.IsArray())
			{
				printf("\n----------\nError: Vehicles array is not array\n----------\n");
				return NULL;
			}

			const Value& vehicleArray = itr->value;
			for (SizeType i = 0; i < vehicleArray.Size(); i++)
			{
				if (decodeVehicle(state, vehicleArray[i]) == -1)
				{
					printf("\n----------\nError decoding vehicles\n----------\n");
					return NULL;
				}
			}
		}

		/*
		 * BULLETS
		 */
		if (strcmp(itr->name.GetString(), "Bullets") == 0)
		{
			// If Bullets is not an array, something went wrong
			if (!itr->value.IsArray())
			{
				printf("\n----------\nError: Bullets array is not array\n----------\n");
				return NULL;
			}

			const Value& bulletArray = itr->value;
			for (SizeType i = 0; i < bulletArray.Size(); i++)
			{
				if (decodeBullet(state, bulletArray[i]) == -1)
				{
					printf("\n----------\nError decoding bullets\n----------\n");
					return NULL;
				}
			}
		}
	}

	/*
	 * BASES
	 * TODO: replace with actual decoding when the server returns bases
	 */
	double x, y;
	x = 100, y = 100;
	int health, team, width, height;
	health = 100000, team = 0, width = height = 100;
	Base* new_base = new Base((int) x, (int) y, health, team, width, height);
	state->addBase(new_base);
	x = 300, y = 100, health = 109, team = 1;
	new_base = new Base((int) x, (int) y, health, team, width, height);
	state->addBase(new_base);

	return state;
}

int JsonEncodeDecode::decodeVehicle(GameState* state, const Value& vehicle)
{
	// Vehicle vars
	double x, y, velocity, angle;
	x = y = velocity = angle = 0;
	int width, height, team, health;
	width = height = team = health = 0;

	// Iterate through JSON vehicle object
	const char* check;
	for (Value::ConstMemberIterator itr = vehicle.MemberBegin(); itr != vehicle.MemberEnd(); ++itr)
	{
		check = itr->name.GetString();

		if (strcmp(check, "X") == 0)
		{
			x = itr->value.GetDouble();
			continue;
		}
		if (strcmp(check, "Y") == 0)
		{
			y = itr->value.GetDouble();
			continue;
		}
		if (strcmp(check, "Width") == 0)
		{
			width = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Height") == 0)
		{
			height = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "Velocity") == 0)
		{
			velocity = itr->value.GetDouble();
			continue;
		}
		if (strcmp(check, "Angle") == 0)
		{
			angle = itr->value.GetDouble();
			continue;
		}
		if (strcmp(check, "CurrentHealth") == 0)
		{
			health = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "TeamId") == 0)
		{
			team = itr->value.GetInt();
			continue;
		}
	}
	// TODO: replace with decoding from serverside to find isMe field
	bool isMe = false;

	// Create a new Vehicle
	Vehicle* new_vehicle = new Vehicle((int) x, (int) y, health, angle, velocity, team, width, height, isMe);

	// Push it to the GameState
	state->addPlayer(new_vehicle);

	return 1;
}

int JsonEncodeDecode::decodeBullet(GameState *state, const Value &bullet)
{
	// Bullet vars
	double x, y;
	x = y = 0;
	int radius;
	radius = 0;

	// Iterate through JSON bullet object
	const char* check;
	for (Value::ConstMemberIterator itr = bullet.MemberBegin(); itr != bullet.MemberEnd(); ++itr)
	{
		check = itr->name.GetString();

		if (strcmp(check, "X") == 0)
		{
			x = itr->value.GetDouble();
			continue;
		}
		if (strcmp(check, "Y") == 0)
		{
			y = itr->value.GetDouble();
			continue;
		}
		if (strcmp(check, "Width") == 0)
		{
			radius = itr->value.GetInt();
			continue;
		}
	}

	// Create a new Bullet
	Bullet* new_bullet = new Bullet((int) x, (int) y, radius);

	// Push it to the GameState
	state->addBullet(new_bullet);

	return 1;
}