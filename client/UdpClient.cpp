#include "UdpClient.h"
#include "EncodeDecode.h"
#include "JsonEncodeDecode.h"
#include "FakeServer.h"

#include <arpa/inet.h>

int UdpClient::connect_to_server(const char *host, const char *port)
{
	int sockfd;
	ssize_t n;
	struct sockaddr_in servaddr;
	char sendline[1000];
	char recvline[1000];

	sockfd=socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(host);
	servaddr.sin_port = htons(32000);

	while (fgets(sendline, 10000, stdin) != NULL)
	{
		printf(sendline);
		sendto(sockfd, sendline, strlen(sendline), 0,
			   (struct sockaddr *) &servaddr, sizeof(servaddr));
		n = recvfrom(sockfd, recvline, 10000, 0, NULL, NULL);
		recvline[n] = 0;
		fputs(recvline, stdout);
	}

	return 0;
}
/*
int UdpClient::error(const char *msg)
{
	perror(msg);
	return -1;
}

int UdpClient::connect_to_server(const char *host, const char *port)
{
	// Mock up section
	printf("Connected to host %s through port %s. (not really, this is a mockup)", host, port);
	return 0;

	int port_num;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	// Open socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		return error("ERROR: cannot open socket");
	}

	// Find server
	server = gethostbyname(host);
	if (server == NULL)
	{
		return error("ERROR: host not found");
	}

	// Get port number
	port_num = atoi(port);

	// Set the server's address
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr, (size_t) server->h_length);
	serv_addr.sin_port = htons((uint16_t) port_num);

	// Connect to server
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		return error("ERROR: could not connect");
	}

	return 0;
}

int UdpClient::send_command(const char *command)
{
	// Send encoded command to server
	EncodeDecode* encodeDecode = new JsonEncodeDecode;
	command = encodeDecode->encode(command);

	// Mock up section
	printf("Sent command:\n%s", command);
	return 0;

	if (write(sockfd, command, strlen(command)) < 0)
	{
		return error("ERROR: could not write to socket");
	}

	return 0;
}

int UdpClient::get_game_state(char *buffer)
{
	EncodeDecode* encodeDecode = new JsonEncodeDecode;

	// Mock up section
	FakeServer* fakeServer = new FakeServer;
	fakeServer->read(buffer);
	buffer = encodeDecode->decode(buffer);
	return 0;

	// Receive response from server, decode
	printf("Return message:\n");
	bzero(buffer, 256);
	if (read(sockfd, buffer, 255) < 0)
	{
		return error("ERROR: could not read from socket");
	}

	buffer = encodeDecode->decode(buffer);

	return 0;
}

int UdpClient::close_connection()
{
	// Mock up section
	return 0;

	// Close socket
	if (close(sockfd) < 0)
	{
		return error("ERROR: could not close socket");
	}

	return 0;
}
 */