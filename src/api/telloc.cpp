#include "api/telloc.h"
#include "api/telloc_types.h"

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

void FreeTellocResponse(TellocResponseTypePtr responsePtr)
{
	// Delete anything within the response that was dynamically allocated
	switch (responsePtr->type)
	{
	case 2:
	case 3:
	case 4:
		delete[] responsePtr->str;
		responsePtr->str = nullptr;
		responsePtr->len = 0;
		break;
	}

	delete responsePtr;
	responsePtr = nullptr;
}

TellocResponseTypePtr TellocCommand(TellocInstancePtr tellocInstancePtr, const char* cmd)
{
	return tellocInstancePtr->ExecuteCommand(cmd);
}
