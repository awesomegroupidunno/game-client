#ifndef GAME_CLIENT_UDPCLIENT_H
#define GAME_CLIENT_UDPCLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "NetworkClient.h"
#include "JsonEncodeDecode.h"
#include "Listener.h"

class UdpClient : public NetworkClient
{
private:
	int sockfd;
	struct sockaddr_in servaddr;
	EncodeDecode* encodeDecode = new JsonEncodeDecode;

	int error(const char* msg);

public:
	int connect_to_server(const char* host, const char* port);
	int send_command(char* command);
	int start_listening();
	void update(char* buffer);
	int close_connection();
};

#endif //GAME_CLIENT_UDPCLIENT_H
