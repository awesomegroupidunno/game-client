#include "Listener.h"

void* listen(void* args)
{
	struct Data* data;
	data = (struct Data*) args;
	int maxBufferSize = 10000;
	char recvline[maxBufferSize];
	ssize_t endPos;
	bool conn = true;

	// Listen forever
	while (conn)
	{
		// Attempt receiving from host
		endPos = recv(data->sockfd, recvline, (size_t) maxBufferSize, 0);

		// Ignore unless a message was received
		if (endPos > 0)
		{
			// Set null-terminating character of received data
			recvline[endPos] = 0;

			// Update client
			pthread_mutex_lock(data->game_state_mutex);
			data->client->update(recvline);
			pthread_mutex_unlock(data->game_state_mutex);
		}
	}

	return NULL;
}

int Listener::create_listener(int sockfd, NetworkClient* client, pthread_mutex_t* game_state_mutex)
{
	// Set data to pass to thread
	data.sockfd = sockfd;
	data.client = client;
	data.game_state_mutex = game_state_mutex;

	// Create thread
	if (pthread_create(&listen_thread, NULL, listen, (void*) &data) != 0)
	{
		perror("error creating client thread");
		return -1;
	}

	printf("Listener created\n");

	return 0;
}