#include "Listener.h"

void* listen(void* args)
{
	struct data* data;
	data = (struct data*) args;
	int maxBufferSize = 1000;
	char recvline[maxBufferSize];
	ssize_t endPos;
	bool conn = true;

	// Listen forever
	while (conn)
	{
		// Attempt receiving from host
		endPos = recv(data->sockfd, recvline, (size_t) maxBufferSize, 0);

		// Ignore unless a message was received
		if (endPos >= 0)
		{
			// Set null-terminating character of received data
			recvline[endPos] = 0;

			// Update client
			data->client->update(recvline);
		}
	}

	return NULL;
}

int Listener::create_listener(int sockfd, NetworkClient* client)
{
	// Set data to pass to thread
	data.sockfd = sockfd;
	data.client = client;

	// Create thread
	if (pthread_create(&listen_thread, NULL, listen, (void*) &data) != 0)
	{
		perror("error creating client thread");
		return -1;
	}

	return 0;
}