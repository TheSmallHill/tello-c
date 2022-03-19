#include "api/telloc.h"

#include "api/telloc_config_internal.h"
#include "telloc_instance_internal.h"

TellocInstancePtr CreateTellocInstance(const TellocConfigPtr configPtr)
{
	return new TellocInstanceInternal(*configPtr);
}

void DestroyTellocInstance(TellocInstancePtr* tellocInstancePtr)
{
	delete *tellocInstancePtr;
	*tellocInstancePtr = nullptr;
}

void FreeTellocResponse(TellocResponsePtr responsePtr)
{
	delete responsePtr;
}

TellocResponsePtr TellocCommand(TellocInstancePtr, const char* format, ...)
{
	// Return a null pointer for now
	return nullptr;
}
