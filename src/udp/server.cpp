#include "udp/server.h"

#include <unistd.h>

#include <cstring>

namespace udp
{
const std::size_t Server::MAX_MESSAGE_SIZE_ = 512;

Server::Server(const std::string& address, const int port)
	: socket_(-1)
	, port_(port)
	, address_(address)
	, addressInfoPtr_(nullptr)
{
	char decimalPort[16];
	snprintf(decimalPort, sizeof(decimalPort), "%d", port_);
	decimalPort[sizeof(decimalPort), sizeof(decimalPort[0]) - 1] = '\0';
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	int r(getaddrinfo(address.c_str(), decimalPort, &hints, &addressInfoPtr_));
	if ((r != 0) || (addressInfoPtr_ == nullptr))
	{
		/// @todo throw an exception
	}
	socket_ = socket(addressInfoPtr_->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
	if (socket_ == -1)
	{
		freeaddrinfo(addressInfoPtr_);
		/// @todo throw an exception
	}
	r = bind(socket_, addressInfoPtr_->ai_addr, addressInfoPtr_->ai_addrlen);
	if (r != 0)
	{
		freeaddrinfo(addressInfoPtr_);
		close(socket_);
		/// @todo throw an exception
	}
}

Server::~Server()
{
	freeaddrinfo(addressInfoPtr_);
	close(socket_);
}

bool Server::ReceiveBlocking(std::string& msg)
{
	char* rawMsg = new char[MAX_MESSAGE_SIZE_];

	const int returnVal = recv(socket_, reinterpret_cast<void*>(rawMsg), MAX_MESSAGE_SIZE_, 0);

	msg.assign(rawMsg, returnVal);

	delete rawMsg;
	rawMsg = nullptr;

	return !msg.empty();
}

bool Server::ReceiveNonBlocking(const unsigned int timeout_ms, std::string& msg)
{
	bool status = false;

	fd_set s;
	FD_ZERO(&s);
	FD_SET(socket_, &s);
	struct timeval timeout;
	const int timeout_ms_internal = static_cast<int>(timeout_ms);
	timeout.tv_sec = timeout_ms_internal / 1000;
	timeout.tv_usec = (timeout_ms_internal % 1000) * 1000;

	const int retVal = select(socket_ + 1, &s, &s, &timeout);
	if (retVal == -1)
	{
		status = false;
	}
	else if (retVal > 0)
	{
		char* rawMsg = new char[MAX_MESSAGE_SIZE_];
		const int numBytes = recv(socket_, reinterpret_cast<void*>(msg), MAX_MESSAGE_SIZE_, 0);

		msg.assign(rawMsg, numBytes);

		delete rawMsg;
		rawMsg = nullptr;

		status = !msg.empty();
	}

	errno = EAGAIN;

	return status;
}
}
