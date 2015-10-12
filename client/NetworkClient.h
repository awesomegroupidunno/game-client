#ifndef GAME_CLIENT_NETWORKCLIENT_H
#define GAME_CLIENT_NETWORKCLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "JsonEncodeDecode.h"
#include "Listener.h"

class NetworkClient
{
public:
	virtual int connect_to_server(const char* host, const char* port) = 0;
	virtual int send_command(Command* c) = 0;
	virtual int start_listening() = 0;
	virtual void update(char* buffer) = 0;
	virtual int close_connection() = 0;

	// Commands
	virtual void connect_command() = 0;
	virtual void move_command(int dir) = 0;
	virtual void turn_command(int dir) = 0;
};

#endif //GAME_CLIENT_NETWORKCLIENT_H
