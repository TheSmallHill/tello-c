#include "udp/client.h"

#include <unistd.h>

#include <cstring>

namespace udp
{
Client::Client(const std::string& address, const int port)
	: socket_(-1)
	, port_(port)
	, address_(address)
	, addressInfoPtr_(nullptr)
{
	char decimalPort[16];
	snprintf(decimalPort, sizeof(decimalPort), "%d", port);
	decimalPort[sizeof(decimalPort)/sizeof(decimalPort[0]) - 1] = '\0';

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	int r(getaddrinfo(address.c_str(), decimalPort, &hints, &addressInfoPtr_));
	if ((r != 0) || (addressInfoPtr_ == nullptr))
	{
		// Throw exception
	}

	// Create socket and check result
	socket_ = socket(addressInfoPtr_->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
	if (socket_ == -1)
	{
		freeaddrinfo(addressInfoPtr_);

		// Throw exception
	}
}

Client::~Client()
{
	freeaddrinfo(addressInfoPtr_);
	close(socket_);
}

int Client::Send(const std::string& msg)
{
	return sendto(socket_, msg.c_str(), msg.length(), 0, addressInfoPtr_->ai_addr, addressInfoPtr_->ai_addrlen);
}
}
