#include "UdpClient.h"

UdpClient::UdpClient()
{
	this->encodeDecode = new JsonEncodeDecode;
}

UdpClient::~UdpClient()
{
	delete encodeDecode;
}

void UdpClient::set_controller(GameController* controller)
{
	this->controller = controller;
}

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

	printf("Connected to host %s through port %s on socket fd %i\n", host, port, sockfd);

	return 0;
}

int UdpClient::send_command(Command* c, int mode)
{
	ssize_t err;
	const char* sendline;

	// Encode JSON
	sendline = encodeDecode->encode(c, mode);

	// Send the command to the host
	err = send(sockfd, sendline, strlen(sendline), 0);
	if (err < 0)
	{
		return error("error sending to host");
	}

	printf("sent:\n%s\n", sendline);

	return 0;
}

int UdpClient::start_listening()
{
	Listener* listener = new Listener;
	listener->create_listener(sockfd, this);

	return 0;
}

void UdpClient::update(char* update)
{
	// Create a new GameState
	GameState* new_state = encodeDecode->decode(update);

	// Replace old with new
	if (new_state != NULL)
	{
		controller->update(new_state);
	}

	printf("recv:\n%s\n", update);
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

/*
 * Commands
 */

void UdpClient::connect_command()
{
	Command* c = new Command;

	c->type = "POST";
	c->subtype = "CONNECT";
	c->strValue = "username";

	send_command(c, STRING_MODE);

	delete c;
}

void UdpClient::move_command(int dir)
{
	Command* c = new Command;

	c->type = "POST";
	c->subtype = "ACCELERATION";
	c->numValue = dir;

	send_command(c, NUM_MODE);

	delete c;
}

void UdpClient::turn_command(int dir)
{
	Command* c = new Command;

	c->type = "POST";
	c->subtype = "TURN";
	c->numValue = dir;

	send_command(c, NUM_MODE);

	delete c;
}