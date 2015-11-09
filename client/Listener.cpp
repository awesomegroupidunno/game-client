#include "Listener.h"

void* listen(void* args)
{
	struct Data *data;
	data = (struct Data *) args;
	int maxBufferSize = 100000;
	char recvline[maxBufferSize];
	std::string recvstring;
	ssize_t endPos;
	GameState* new_state;
	bool conn = true;

	// Create new EncodeDecode
	EncodeDecode* encodeDecode = new JsonEncodeDecode;

	// Listen forever
	while (conn)
	{
		/*// Clear out buffer
		recvstring.clear();

		// Attempt receiving from host
		do
		{
			endPos = recv(data->sockfd, recvline, (size_t) maxBufferSize, 0);
			recvline[endPos] = 0;
			recvstring += recvline;

			//printf("recv: %s\nrecv size: %i\n", recvstring.c_str(), (int) endPos);
		}
		while (endPos >= maxBufferSize);

		// Update client
		pthread_mutex_lock(data->game_state_mutex);
		data->client->update(recvstring.c_str());
		pthread_mutex_unlock(data->game_state_mutex);*/

		endPos = recv(data->sockfd, recvline, (size_t) maxBufferSize, 0);

		// Ignore unless a message was received
		if (endPos > 0)
		{
			// Set null-terminating character of received data
			recvline[endPos] = 0;

			// Decode buffer into a new GameState
			new_state = encodeDecode->decode(recvline);

			// Update client
			if (new_state != NULL)
			{
				pthread_mutex_lock(data->game_state_mutex);
				data->client->update(new_state);
				pthread_mutex_unlock(data->game_state_mutex);
			}

			printf("recv:\n%s\n", recvline);
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