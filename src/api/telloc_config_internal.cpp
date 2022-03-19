#include "api/telloc_config_internal.h"

const char* TellocConfigInternal::DEFAULT_IP_ = "192.168.10.1";
const unsigned int TellocConfigInternal::DEFAULT_PORT_ = 8889;

TellocConfigInternal::TellocConfigInternal()
	: ip_(DEFAULT_IP_)
	, port_(DEFAULT_PORT_)
{
	// Intentionally empty since this is just needed to initialize the structure.
}

TellocConfigInternal::~TellocConfigInternal()
{
	// Intentionally empty, nothing complex to destruct.
}
