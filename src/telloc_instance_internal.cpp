#include "api/telloc_types.h"

#include "telloc_instance_internal.h"

#include "udp/client.h"
#include "udp/server.h"

TellocInstanceInternal::TellocInstanceInternal(const TellocConfigInternal& config)
	: config_(config)
	, udpClientPtr_(new udp::Client(config.ip_, config.port_))
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
		const int socketReturn = udpClient_->Send(cmd);
	}

	return replyPtr;
}
