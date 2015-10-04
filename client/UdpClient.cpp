#include "UdpClient.h"

int UdpClient::error(const char *msg)
{
	perror(msg);
	return -1;
}

int UdpClient::connect_to_server(const char *host, const char *port)
{
	// Open socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		return error("error opening socket");
	}

	// Set up the socket's destination (the host)
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(host);
	servaddr.sin_port = htons((uint16_t) atoi(port));

	// Connect to host
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
	{
		return error("error connecting to host");
	}

	printf("Connected to host %s through port %s\n", host, port);

	return 0;
}

int UdpClient::get_game_state(char *buffer)
{
	char recvline[1000];
	ssize_t endPos;

	// Try 100 times to receive from host
	int tries = 0;
	int maxTries = 100;
	bool trying = true;
	char err[] = "";
	do
	{
		endPos = recv(sockfd, recvline, 1000, MSG_DONTWAIT);
		if (endPos < 0)
		{
			sprintf(err, "receiving from host failed, attempt %i", tries + 1);
			error(err);
			tries++;
			if (tries >= maxTries)
			{
				return error("unable to receive from host");
			}
		}
		else
		{
			trying = false;
		}
	} while (trying);

	// Set null-terminating character of received data
	recvline[endPos] = 0;

	printf("rcvd: %s\n", recvline);

	return 0;
}

int UdpClient::send_command(char *command)
{
	ssize_t err;

	// Send the command to the host
	err = send(sockfd, command, strlen(command), 0);
	if (err < 0)
	{
		return error("error sending to host");
	}

	printf("sent: %s\n", command);

	return 0;
}


int UdpClient::close_connection()
{
	// Close socket
	if (close(sockfd) < 0)
	{
		return error("error closing socket");
	}

	return 0;
}