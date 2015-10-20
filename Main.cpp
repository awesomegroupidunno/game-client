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

void run_client(GameState* state)
{
	NetworkClient* client = new UdpClient(state);

	// Connect to server
//	client->connect_to_server("172.31.1.42", "10001");
	client->connect_to_server("127.0.0.1", "10001");

	// Start up listener thread
	client->start_listening();

	// Tell the server we exist
	client->connect_command();

	// Send a command
	client->move_command(1);
	client->turn_command(-1);

	// for debugging purposes, prevent from listening for too long
	sleep(1);
	client->close_connection();

	delete client;
}

int main()
{
	// TODO: The following is an idea of how the main loop should function
	// Initialize GameView
	/*
	 * THE FOLLOWING IS ONLY A TEST OF WHAT THE STRUCTURE SHOULD LOOK LIKE
	 * TESTS: Vehicles drawing on screen
	 */

	GameState* state = new GameState;

	/*GameController* controller = new GameController;
	SdlInputAdapter* inputAdapter = new SdlInputAdapter(controller);
	SdlGameViewAdapter* gameViewAdapter = new SdlGameViewAdapter(controller);
	SdlGameView screen(gameViewAdapter, inputAdapter);
	screen.drawView();*/

	// TODO: The following is a test for server connectivity
	// Start up client
	run_client(state);

	return 0;
}