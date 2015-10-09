#include "Listener.h"

struct data
{
	NetworkClient* client;
	int sockfd;
};

void* listen(void* args)
{
	struct data* data;
	data = (struct data*) args;
	int maxBufferSize = 1000;
	char recvline[maxBufferSize];
	ssize_t endPos;

	printf("thread sockfd: %i\n", data->sockfd);

	// Listen forever
	while (true)
	{
		// Attempt receiving from host
		endPos = recv(data->sockfd, recvline, (size_t) maxBufferSize, MSG_WAITALL);

		// Ignore unless a message was received
		if (endPos >= 0)
		{
			// Set null-terminating character of received data
			recvline[endPos] = 0;

			// Update client
			data->client->update(recvline);
		}
	}
}

/*
 *
 * TODO: fix!
 * It will receive once from the server, but stops after that.
 * The loop is still going, it just continually returns a -1 from recv().
 *
 * Also, calling data->client->update() is segfaulting. COOL
 *
 */

int Listener::create_listener(int sockfd, NetworkClient* client)
{
	// Set data to pass to thread
	struct data data;
	data.sockfd = sockfd;
	data.client = client;

	printf("listener sockfd: %i\n", data.sockfd);

	// Create thread
	if (pthread_create(&listen_thread, NULL, listen, (void*) &data) != 0)
	{
		perror("error creating client thread");
		return -1;
	}

	// For some reason, without this an incorrect sockfd value is passed to the thread
	sleep(1);

	return 0;
}