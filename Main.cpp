#include "SdlGameView.cpp"
#include "UdpClient.h"

/*
 * NOTE: GameState.cpp and Vehicle.h usually would NOT be here.
 *      GameState would usually be set by the server.
 *      For the sake of testing, main has been hardcoded
 *      to initialize GameState and Vehicles.
 */

void run_client()
{
	NetworkClient* client = new UdpClient;

	// Close the connection in case it's already open
	client->close_connection();

	// Connect to server
	client->connect_to_server("127.0.0.1", "10001");

	// Start up listener thread
	client->start_listening();

	// Send a command
	client->move_command(1);
	client->turn_command(-1);

	// for debugging purposes, prevent from listening for too long
	sleep(1);
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

	// Start up client
	run_client();

	// Stay connected forever
	while (true)
	{
		sleep(1);
	}

	return 0;
}