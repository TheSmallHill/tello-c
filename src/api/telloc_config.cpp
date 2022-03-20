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

void SetCommandPort(TellocConfigPtr configPtr, const unsigned int port)
{
	configPtr->commandPort_ = port;
}

void SetStatePort(TellocConfigPtr configPtr, const unsigned int port)
{
	configPtr->statePort_ = port;
}

const char* GetIpAddress(const TellocConfigPtr configPtr)
{
	return configPtr->ip_.c_str();
}

unsigned int GetCommandPort(const TellocConfigPtr configPtr)
{
	return configPtr->commandPort_;
}

unsigned int GetStatePort(const TellocConfigPtr configPtr)
{
	return configPtr->statePort_;
}
