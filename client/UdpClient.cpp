#include "UdpClient.h"
#include "EncodeDecode.h"
#include "JsonEncodeDecode.h"
#include "FakeServer.h"

#include <arpa/inet.h>

int UdpClient::error(const char *msg)
{
	perror(msg);
	return -1;
}

int UdpClient::connect_to_server(const char *host, const char *port)
{
	ssize_t n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		return error("error opening socket");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(host);
	servaddr.sin_port = htons((uint16_t) atoi(port));

	printf("Connected to host %s through port %s\n", host, port);

	return 0;
}

int UdpClient::get_game_state(char *buffer)
{
	char recvline[1000];
	ssize_t endPos;

	// Receive from connection
	endPos = recvfrom(sockfd, recvline, 10000, 0, NULL, NULL);
	if (endPos < 0)
	{
		return error("error receiving from host");
	}

	recvline[endPos] = 0;

	printf("rcvd: %s\n", recvline);

	return 0;
}

int UdpClient::send_command(char *command)
{
	ssize_t err;

	// Send command is in stdin
	err = sendto(sockfd, command, strlen(command), 0,
			   (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (err < 0)
	{
		return error("error sending to host");
	}

	printf("sent: %s\n", command);

	return 0;
}

/*int UdpClient::send_command(char *command)
{
	char sendline[1000];
	ssize_t err;
	printf("%s\n", command);

	// Send whatever is in stdin
	while (fgets(sendline, 10000, stdin) != NULL)
	{
		printf("test\n");
		err = sendto(sockfd, sendline, strlen(sendline), 0,
					 (struct sockaddr *) &servaddr, sizeof(servaddr));
		if (err < 0)
		{
			return error("error sending to host");
		}

		printf("%s", sendline);
	}

	return 0;
}*/

int UdpClient::close_connection()
{
	// Close socket
	if (close(sockfd) < 0)
	{
		return error("error closing socket");
	}

	return 0;
}