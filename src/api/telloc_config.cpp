#include "api/telloc_config.h"

#include "api/telloc_config_internal.h"

TellocConfigPtr CreateTellocConfigInstance()
{
	return new TellocConfigInternal();
}

void DestroyTellocConfigInstance(TellocConfigPtr* configPtr)
{
	delete *configPtr;
	*configPtr = nullptr;
}

void SetIpAddress(TellocConfigPtr configPtr, const char* ip)
{
	configPtr->ip_.assign(ip);
}

void SetPort(TellocConfigPtr configPtr, const unsigned int port)
{
	configPtr->port_ = port;
}
