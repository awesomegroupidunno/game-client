#include "SdlGameView.h"
#include "UdpClient.h"

NetworkClient* run_client()
{
	NetworkClient* client = new UdpClient();

	client->close_connection();

	// Connect to server
//	client->connect_to_server("172.31.1.42", "10001");
	client->connect_to_server("127.0.0.1", "10001");

	// Start up listener thread
	client->start_listening();

	// Tell the server we exist
	client->connect_command();

	return client;
}

int main()
{
	// Start up client
	NetworkClient* client = run_client();

	// Init main game loop
	GameState* state = new GameState();
	GameController* controller = new GameController(state, client);
	SdlInputAdapter* inputAdapter = new SdlInputAdapter(controller);
	SdlGameViewAdapter* gameViewAdapter = new SdlGameViewAdapter(controller);
	SdlGameView screen(gameViewAdapter, inputAdapter);
	screen.drawView();

	return 0;
}