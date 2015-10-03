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
	const char* command = "Hello Car Combat!";
	char* buffer;
	bool connected = true;

	client->connect_to_server("127.0.0.1", "10001");

	while (connected)
	{
		//client->send_command(command);
		//client->get_game_state(buffer);

		printf(buffer);
	}

	//client->close_connection();
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