#include "SdlGameView.h"
#include "UdpClient.h"

NetworkClient* run_client(pthread_mutex_t* game_state_mutex)
{
	NetworkClient* client = new UdpClient();

	client->close_connection();

	// Connect to server
//	client->connect_to_server("172.31.1.42", "10001");
	client->connect_to_server("172.31.1.41", "10001");
//	client->connect_to_server("127.0.0.1", "10001");
//	client->connect_to_server("192.168.156.25", "10001");

	// Start up listener thread
	client->start_listening(game_state_mutex);

	// Tell the server we exist
	client->connect_command();

	return client;
}

int main()
{
	pthread_mutex_t game_state_mutex;
	pthread_mutex_init(&game_state_mutex, NULL);

	// Start up client
	NetworkClient* client = run_client(&game_state_mutex);

	// Init main game loop
	GameState* state = new GameState();
	GameController* controller = new GameController(state, client, &game_state_mutex);
	SdlInputAdapter* inputAdapter = new SdlInputAdapter(controller);
	SdlGameViewAdapter* gameViewAdapter = new SdlGameViewAdapter(controller);
	SdlGameView screen(gameViewAdapter, inputAdapter);
	screen.drawView();

	return 0;
}