#include "SdlGameView.cpp"
#include "UdpClient.h"

using namespace std;

/*
 * NOTE: GameState.cpp and Vehicle.h usually would NOT be here.
 *      GameState would usually be set by the server.
 *      For the sake of testing, main has been hardcoded
 *      to initialize GameState and Vehicles.
 */

void run_client()
{
	NetworkClient* client = new UdpClient;
	char command[] = "{\"Type\":\"POST\",\"Subtype\":\"TURN\",\"Value\":1.0,\"UniqueID\":\"123\"}";
	char buffer[1000];
	bool connected = true;

	client->close_connection();

	client->connect_to_server("127.0.0.1", "10001");
	client->start_listening(buffer);

	while (connected)
	{
		client->send_command(command);
		sleep(1);

		//connected = false;
	}

	client->close_connection();
}

int main()
{
	// TODO: The following is an idea of how Main.cpp should look
	// Draw window / game screen
	// Initialize game loop / GameController.cpp
	// Handle exiting game
	/*
	 * THE FOLLOWING IS ONLY A TEST OF WHAT THE STRUCTURE SHOULD LOOK LIKE
	 * ALSO TESTS DRAWING VEHICLES ON SCREEN
	 */
	//SdlGameView screen;
	//screen.drawView();

	run_client();

	return 0;
}