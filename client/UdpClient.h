#ifndef GAME_CLIENT_UDPCLIENT_H
#define GAME_CLIENT_UDPCLIENT_H

#include "NetworkClient.h"

class UdpClient : public NetworkClient
{
private:
	int sockfd;
	struct sockaddr_in servaddr;
	EncodeDecode* encodeDecode = new JsonEncodeDecode;

	int error(const char* msg);

public:
	int connect_to_server(const char* host, const char* port);
	int send_command(Command* c, int mode);
	int start_listening();
	void update(char* update);
	int close_connection();

	// Commands
	void connect_command();
	void move_command(int dir);
	void turn_command(int dir);
};

#endif //GAME_CLIENT_UDPCLIENT_H
