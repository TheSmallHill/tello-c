#include "api/telloc_config_internal.h"

const char* TellocConfigInternal::DEFAULT_IP_ = "192.168.10.1";
const unsigned int TellocConfigInternal::DEFAULT_COMMAND_PORT_ = 8889;
const unsigned int TellocConfigInternal::DEFAULT_STATE_PORT_ = 8890;
const unsigned int TellocConfigInternal::DEFAULT_COMMAND_RESPONSE_TIMEOUT_MS_ = 5000;

TellocConfigInternal::TellocConfigInternal()
	: ip_(DEFAULT_IP_)
	, commandPort_(DEFAULT_COMMAND_PORT_)
	, statePort_(DEFAULT_STATE_PORT_)
	, commandResponseTimeout_ms_(DEFAULT_COMMAND_RESPONSE_TIMEOUT_MS_)
{
	// Intentionally empty since this is just needed to initialize the structure.
}

TellocConfigInternal::~TellocConfigInternal()
{
	// Intentionally empty, nothing complex to destruct.
}
