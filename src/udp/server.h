#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string>

namespace udp
{
class Server
{
public:
	Server(const std::string& address, const int port);

	virtual ~Server();

	bool ReceiveBlocking(std::string& msg);

	bool ReceiveNonBlocking(const unsigned int timeout_ms, std::string& msg);

protected:
	int socket_;
	const int port_;
	const std::string address_;
	struct addrinfo* addressInfoPtr_;

	static const std::size_t MAX_MESSAGE_SIZE_;
};
}

#endif
