// Determines what kind of value to send
#define NUM_MODE 1
#define STRING_MODE 2

struct Command
{
	char const* type;
	char const* subtype;
	double numValue;
	char const* strValue;
};