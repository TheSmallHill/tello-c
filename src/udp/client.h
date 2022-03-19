#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string>

namespace udp
{
class Client
{
public:
	Client(const std::string& address, const int port);

	virtual ~Client();

	int Send(const std::string& msg);

protected:
	int socket_;
	const int port_;
	const std::string address_;
	struct addrinfo* addressInfoPtr_;
};
}

#endif
