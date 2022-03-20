#include "api/telloc_types.h"

#include "telloc_instance_internal.h"

#include "udp/client.h"
#include "udp/server.h"

#include <cstring>

const char* OK_RESPONSE_STRING_ = "OK";
const char* ERROR_RESPONSE_STRING_ = "ERROR";

TellocInstanceInternal::TellocInstanceInternal(const TellocConfigInternal& config)
	: config_(config)
	, udpCommandClientPtr_(new udp::Client(config.ip_, config.commandPort_))
	, udpCommandResponseServerPtr_(new udp::Server(config.ip_, config.commandPort_))
	, udpStateServerPtr_(new udp::Server(config.ip_, config.statePort_))

{
	// Intentionally empty
}

TellocInstanceInternal::~TellocInstanceInternal()
{
	// Intentionally empty, everything using shared memory making for easy cleanup.
}

TellocResponse* TellocInstanceInternal::ExecuteCommand(const std::string& cmd)
{
	TellocResponse* replyPtr = nullptr;

	// Need a non empty command in order to do anything
	if (!cmd.empty())
	{
		// Send the command to the Tello, save return just in case we get a bad response from Tello or we just timeout
		const int socketReturn = udpCommandClientPtr_->Send(cmd);

		// Immediately start waiting for a response
		std::string responseMsg;
		const bool rcvStatus = udpCommandResponseServerPtr_->ReceiveNonBlocking(config_.commandResponseTimeout_ms_, responseMsg);

		if (rcvStatus)
		{
			// Actually got a response so handle it
			if (responseMsg.find(OK_RESPONSE_STRING_) != std::string::npos)
			{

			}
			else if (responseMsg.find(ERROR_RESPONSE_STRING_) != std::string::npose)
			{

			}
			else
			{

			}
		}
		else
		{
			// Unable to receive anything before timeout, use socket return from send to come up with a return
			replyPtr = new TellocResponse();
			replyPtr->type = static_cast<int>(ResponseType::TELLOC_ERROR);
			replyPtr->str = CreateSocketErrorMessage();
			replyPtr->len = strlen(replyPtr->str);
		}
	}

	return replyPtr;
}

char* TellocInstanceInternal::CreateSocketErrorMessage()
{
	char* errorMessage = nullptr;
	switch(errno)
	{
	case EACCES:
	{
		const char* msg = "Write permission denied on destination socket file, or search permission is denied for one of the directories the path prefix.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EAGAIN /* | EWOULDBLOCK */:
	{
		const char* msg = "Write permission is denied on the destination socket file, or search permission is denied for one of the directories the path prefix.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EBADF:
	{
		const char* msg = "An invalid descriptor was specified.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ECONNRESET:
	{
		const char* msg = "Connection reset by peer.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EDESTADDRREQ:
	{
		const char* msg = "The socket is not connection-mode, and no peer address is set.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EFAULT:
	{
		const char* msg = "An invalid user space address was specified for an argument.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EINTR:
	{
		const char* msg = "A signal occurred before any data was transmitted.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EINVAL:
	{
		const char* msg = "Invalid argument passed.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EISCONN:
	{
		const char* msg = "The connection-mode socket was connected already but a recipient was specified.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EMSGSIZE:
	{
		const char* msg = "The socket type requires that message be sent atomically, and the size of the message to be sent made this impossible.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOBUFS:
	{
		const char* msg = "The output queue for a network interface is full.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOMEM:
	{
		const char* msg = "No memory available";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOTCONN:
	{
		const char* msg = "The socket is not connected, and no target has been given.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOTSOCK:
	{
		const char* msg = "The argument for sockfd is not a socket";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EOPNOTSUPP:
	{
		const char* msg = "Some bit in the flags argument is inappropriate for the socket type";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EPIPE:
	{
		const char* msg = "The local end has been shut down on a connection oriented socket.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	default:
	{
		const char* msg = "Unknown socket error detected!";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	}

	return errorMessage;
}
