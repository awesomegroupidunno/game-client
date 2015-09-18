#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	// Arg checking
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s hostname port\n", argv[0]);
	}

	int sockfd, portNum;
	char buffer[256];
	struct sockaddr_in serv_addr;
	struct hostent *server;

	// Open socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("ERROR: cannot open socket");
	}

	// Find server
	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		error("ERROR: host not found");
	}

	// Get port number
	portNum = atoi(argv[2]);

	// Set the server's address
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr, (size_t) server->h_length);
	serv_addr.sin_port = htons((uint16_t) portNum);

	// Connect to server
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error ("ERROR: could not connect");
	}

	// Get user input, send to server
	printf("Please enter message: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	if (write(sockfd, buffer, strlen(buffer)) < 0)
	{
		error("ERROR: could not write to socket");
	}

	// Receive response from server, print
	printf("Return message:\n");
	bzero(buffer, 256);
	if (read(sockfd, buffer, 255) < 0)
	{
		error("ERROR: could not read from socket");
	}
	printf("%s\n", buffer);

	// Close socket
	close(sockfd);

	return 0;
}