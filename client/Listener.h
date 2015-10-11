#ifndef GAME_CLIENT_LISTENER_H
#define GAME_CLIENT_LISTENER_H

#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include "NetworkClient.h"

class NetworkClient;

struct Data
{
	NetworkClient* client;
	int sockfd;
};

class Listener
{
private:
	pthread_t listen_thread;
	struct Data data;
public:
	int create_listener(int sockfd, NetworkClient* client);
};


#endif //GAME_CLIENT_LISTENER_H
