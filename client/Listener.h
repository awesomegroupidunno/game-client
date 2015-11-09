#ifndef GAME_CLIENT_LISTENER_H
#define GAME_CLIENT_LISTENER_H

#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include "NetworkClient.h"
#include "EncodeDecode.h"

class NetworkClient;

struct Data
{
	NetworkClient* client;
	int sockfd;
	pthread_mutex_t* game_state_mutex;
};

class Listener
{
private:
	pthread_t listen_thread;
	struct Data data;
public:
	int create_listener(int sockfd, NetworkClient* client, pthread_mutex_t* game_state_mutex);
};


#endif //GAME_CLIENT_LISTENER_H
