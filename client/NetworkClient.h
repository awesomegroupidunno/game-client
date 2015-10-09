#ifndef GAME_CLIENT_NETWORKCLIENT_H
#define GAME_CLIENT_NETWORKCLIENT_H

class NetworkClient
{
public:
	virtual int connect_to_server(const char* host, const char* port) = 0;
	virtual int send_command(char* command) = 0;
	virtual int start_listening() = 0;
	virtual void update(char* buffer) = 0;
	virtual int close_connection() = 0;
};

#endif //GAME_CLIENT_NETWORKCLIENT_H
