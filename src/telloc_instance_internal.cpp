#include "api/telloc_types.h"

#include "telloc_instance_internal.h"

#include "udp/client.h"

TellocInstanceInternal::TellocInstanceInternal(const TellocConfigInternal& config)
	: config_(config)
	, udpClient_(new udp::Client(config.ip_, config.port_))
{
	// Intentionally empty
}

TellocInstanceInternal::~TellocInstanceInternal()
{
	// Intentionally empty, everything using shared memory making for easy cleanup.
}

TellocResponse* ExecuteCommand(const std::string& cmd);
