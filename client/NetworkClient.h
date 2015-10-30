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

// TODO: fix CMakeLists so we don't need to do file path stuff in includes!
#include "../GameController.h"

class Listener;
class GameController;

class NetworkClient
{
protected:
	GameController* controller;

public:
	virtual void set_controller(GameController* controller) = 0;
	virtual int connect_to_server(const char* host, const char* port) = 0;
	virtual int send_command(Command* c, int mode) = 0;
	virtual int start_listening(pthread_mutex_t* game_state_mutex) = 0;
	virtual void update(char* update) = 0;
	virtual int close_connection() = 0;

	// Commands
	virtual void connect_command() = 0;
	virtual void move_command(double dir) = 0;
	virtual void turn_command(double dir) = 0;
};

#endif //GAME_CLIENT_NETWORKCLIENT_H
