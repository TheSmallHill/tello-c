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
