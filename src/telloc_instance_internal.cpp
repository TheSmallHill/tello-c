#include "api/telloc_types.h"

#include "telloc_instance_internal.h"

#include "udp/client.h"
#include "udp/server.h"

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
	}

	return replyPtr;
}
