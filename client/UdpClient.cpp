#include "UdpClient.h"

int UdpClient::error(const char* msg)
{
	perror(msg);
	return -1;
}

int UdpClient::connect_to_server(const char* host, const char* port)
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
	if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
	{
		return error("error connecting to host");
	}

	printf("Connected to host %s through port %s: sockfd %i\n", host, port, sockfd);

	return 0;
}

int UdpClient::get_game_state(char* buffer)
{
	int maxBufferSize = 1000;
	char recvline[maxBufferSize];
	ssize_t endPos;

	// Receive from host
	endPos = recv(sockfd, recvline, (size_t) maxBufferSize, 0);
	if (endPos < 0)
	{
		error("error receiving from host");
	}

	// Set null-terminating character of received data
	recvline[endPos] = 0;

	// Decode JSON
	EncodeDecode* encodeDecode = new JsonEncodeDecode;
	buffer = encodeDecode->decode(recvline);

	printf("rcvd:\n%s\n", buffer);

	return 0;
}

int UdpClient::start_listening(char *buffer)
{
	Listener* listener = new Listener;
	listener->create_listener(sockfd, this);

	return 0;
}

void UdpClient::update(char* buffer)
{
	printf("recv:\n%s\n", buffer);
}

int UdpClient::send_command(char* command)
{
	ssize_t err;
	const char* sendline;

	// Encode JSON
	EncodeDecode* encodeDecode = new JsonEncodeDecode;
	sendline = encodeDecode->encode(command);

	// Send the command to the host
	err = send(sockfd, sendline, strlen(sendline), 0);
	if (err < 0)
	{
		return error("error sending to host");
	}

	printf("sent:\n%s\n", sendline);

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