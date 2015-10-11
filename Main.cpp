#include "SdlGameView.h"
#include "SdlInputAdapter.h"
#include "SdlGameViewAdapter.h"
#include "GameController.h"
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
	// TODO: The following is an idea of how the main loop should function
	// Initialize GameView
	/*
	 * THE FOLLOWING IS ONLY A TEST OF WHAT THE STRUCTURE SHOULD LOOK LIKE
	 * TESTS: Vehicles drawing on screen
	 */
	GameController* controller = new GameController;
	SdlInputAdapter* inputAdapter = new SdlInputAdapter(controller);
	SdlGameViewAdapter* gameViewAdapter = new SdlGameViewAdapter(controller);
	SdlGameView screen(gameViewAdapter, inputAdapter);
	screen.drawView();

	/*
	// TODO: The following is a test for server connectivity
	// Start up client
	run_client();

	// Stay connected forever
	while (true)
	{
		sleep(1);
	}
	 */

	return 0;
}