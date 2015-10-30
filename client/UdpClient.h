#ifndef GAME_CLIENT_UDPCLIENT_H
#define GAME_CLIENT_UDPCLIENT_H

#include "NetworkClient.h"

class UdpClient : public NetworkClient
{
private:
	int sockfd;
	struct sockaddr_in servaddr;
	EncodeDecode* encodeDecode;

	int error(const char* msg);

public:
	UdpClient();
	~UdpClient();

	void set_controller(GameController* controller);
	int connect_to_server(const char* host, const char* port);
	int send_command(Command* c, int mode);
	int start_listening(pthread_mutex_t* game_state_mutex);
	void update(char* update);
	int close_connection();

	// Commands
	void connect_command();
	void move_command(double dir);
	void turn_command(double dir);
};

#endif //GAME_CLIENT_UDPCLIENT_H
