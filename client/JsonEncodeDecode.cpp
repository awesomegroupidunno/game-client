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

		/*
		 * BASES
		 */
		if (strcmp(itr->name.GetString(), "Bases") == 0)
		{
			// If Bases is not an array, something went wrong
			if (!itr->value.IsArray())
			{
				printf("\n----------\nError: Bases array is not array\n----------\n");
				return NULL;
			}

			const Value& basesArray = itr->value;
			for (SizeType i = 0; i < basesArray.Size(); i++)
			{
				if (decodeBase(state, basesArray[i]) == -1)
				{
					printf("\n----------\nError decoding bases\n----------\n");
					return NULL;
				}
			}
		}

		/*
		 * SHIELDS
		 */
		if (strcmp(itr->name.GetString(), "Shields") == 0)
		{
			// If Shields is not an array, something went wrong
			if (!itr->value.IsArray())
			{
				printf("\n----------\nError: Shields array is not array\n----------\n");
				return NULL;
			}

			const Value& shieldsArray = itr->value;
			for (SizeType i = 0; i < shieldsArray.Size(); i++)
			{
				if (decodeShield(state, shieldsArray[i]) == -1)
				{
					printf("\n----------\nError decoding shields\n----------\n");
					return NULL;
				}
			}
		}

		/*
		 * SHIELD GENERATORS
		 */
		if (strcmp(itr->name.GetString(), "ShieldGenerators") == 0)
		{
			// If ShieldGenerators is not an array, something went wrong
			if (!itr->value.IsArray())
			{
				printf("\n----------\nError: Shield gens array is not array\n----------\n");
				return NULL;
			}

			const Value& shieldGenArray = itr->value;
			for (SizeType i = 0; i < shieldGenArray.Size(); i++)
			{
				if (decodeShieldGen(state, shieldGenArray[i]) == -1)
				{
					printf("\n----------\nError decoding shield gens\n----------\n");
					return NULL;
				}
			}
		}

		/*
		 * POWERUPS
		 */
		if (strcmp(itr->name.GetString(), "PowerUps") == 0)
		{
			// If Powerups is not an array, something went wrong
			if (!itr->value.IsArray())
			{
				printf("\n----------\nError: Powerups array is not array\n----------\n");
				return NULL;
			}

			const Value& powerupArray = itr->value;
			for (SizeType i = 0; i < powerupArray.Size(); i++)
			{
				if (decodePowerup(state, powerupArray[i]) == -1)
				{
					printf("\n----------\nError decoding powerups\n----------\n");
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
	int x, y, angle, width, height, team, health, maxHealth;
	x = y = angle = width = height = team = health = maxHealth = 0;
	bool isMe = false;

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
		if (strcmp(check, "Angle") == 0)
		{
			angle = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "CurrentHealth") == 0)
		{
			health = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "MaxHealth") == 0)
		{
			maxHealth = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "TeamId") == 0)
		{
			team = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "IsMe") == 0)
		{
			isMe = itr->value.GetBool();
			continue;
		}
	}

	// Create a new Vehicle
	Vehicle* new_vehicle = new Vehicle(x, y, health, maxHealth, angle, team, width, height, isMe);

	// Push it to the GameState
	state->addPlayer(new_vehicle);

	return 1;
}

int JsonEncodeDecode::decodeBullet(GameState *state, const Value &bullet)
{
	// Bullet vars
	int x, y, radius;
	x = y = radius = 0;

	// Iterate through JSON bullet object
	const char* check;
	for (Value::ConstMemberIterator itr = bullet.MemberBegin(); itr != bullet.MemberEnd(); ++itr)
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
		if (strcmp(check, "Width") == 0)
		{
			radius = itr->value.GetInt();
			continue;
		}
	}

	// Create a new Bullet
	Bullet* new_bullet = new Bullet(x, y, radius);

	// Push it to the GameState
	state->addBullet(new_bullet);

	return 1;
}

int JsonEncodeDecode::decodeBase(GameState *state, const Value &base)
{
	// Base vars
	int x, y, health, maxHealth, width, id;
	x = y = health = maxHealth = width = id = 0;

	// Iterate through JSON bullet object
	const char* check;
	for (Value::ConstMemberIterator itr = base.MemberBegin(); itr != base.MemberEnd(); ++itr)
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
		if (strcmp(check, "Width") == 0)
		{
			width = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "CurrentHealth") == 0)
		{
			health = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "MaxHealth") == 0)
		{
			maxHealth = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "TeamId") == 0)
		{
			id = itr->value.GetInt();
			continue;
		}
	}

	// Create a new Bullet
	Base* new_base = new Base(x, y, health, maxHealth, id, width, width);

	// Push it to the GameState
	state->addBase(new_base);

	return 1;
}

int JsonEncodeDecode::decodeShield(GameState *state, const Value &shield)
{
	// Shield vars
	int x, y, width, id;
	x = y = width = id = 0;
	bool isEnabled;
	isEnabled = false;

	// Iterate through JSON shield object
	const char* check;
	for (Value::ConstMemberIterator itr = shield.MemberBegin(); itr != shield.MemberEnd(); ++itr)
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
		if (strcmp(check, "Width") == 0)
		{
			width = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "TeamId") == 0)
		{
			id = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "IsEnabled") == 0)
		{
			isEnabled = itr->value.GetBool();
			continue;
		}
	}

	// Create a new Shield
	Shield* new_shield = new Shield(x, y, id, width, width, isEnabled);

	// Push it to the GameState
	state->addShield(new_shield);

	return 1;
}

int JsonEncodeDecode::decodeShieldGen(GameState *state, const Value &shield_gen)
{
	// Generator vars
	int x, y, health, maxHealth, width, id;
	x = y = health = maxHealth = width = id = 0;

	// Iterate through JSON shield generator object
	const char* check;
	for (Value::ConstMemberIterator itr = shield_gen.MemberBegin(); itr != shield_gen.MemberEnd(); ++itr)
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
		if (strcmp(check, "Width") == 0)
		{
			width = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "CurrentHealth") == 0)
		{
			health = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "MaxHealth") == 0)
		{
			maxHealth = itr->value.GetInt();
			continue;
		}
		if (strcmp(check, "TeamId") == 0)
		{
			id = itr->value.GetInt();
			continue;
		}
	}

	// Create a new Generator
	Generator* new_gen = new Generator(x, y, health, maxHealth, id, width, width);

	// Push it to the GameState
	state->addGenerator(new_gen);

	return 1;
}

int JsonEncodeDecode::decodePowerup(GameState *state, const Value &powerup)
{
	// Powerup vars
	int x, y, type, width, height;
	x = y = type = width = height = 0;

	// Iterate through JSON powerup object
	const char* check;
	for (Value::ConstMemberIterator itr = powerup.MemberBegin(); itr != powerup.MemberEnd(); ++itr)
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
		if (strcmp(check, "Type") == 0)
		{
			type = itr->value.GetInt();
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
	}

	// Create a new Powerup
	Powerup* new_powerup = new Powerup(x, y, type, width, height);

	// Push it to the GameState
	state->addPowerup(new_powerup);

	return 1;
}