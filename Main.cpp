#include <iostream>
#include "UdpClient.h"

using namespace std;

int main()
{
	NetworkClient* client = new UdpClient;
	const char* command = "Hello Car Combat!";
	char* buffer;

	client->connect_to_server("", "");
	client->send_command(command);
	client->get_game_state(buffer);
	client->close_connection();
	
	return 0;
}