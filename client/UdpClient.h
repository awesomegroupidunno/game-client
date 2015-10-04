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
#include "EncodeDecode.h"
#include "JsonEncodeDecode.h"

class UdpClient : public NetworkClient
{
private:
	int sockfd;
	struct sockaddr_in servaddr;
	int error(const char* msg);

public:
	int connect_to_server(const char* host, const char* port);
	int send_command(char* command);
	int get_game_state(char* buffer);
	int close_connection();
};

#endif //GAME_CLIENT_UDPCLIENT_H
