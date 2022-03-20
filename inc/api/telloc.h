#ifndef TELLOC_H
#define TELLOC_H

#include "api/telloc_types.h"
#include "api/telloc_config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct TellocInstanceInternal;

typedef struct TellocInstanceInternal* TellocInstancePtr;

TellocInstancePtr CreateTellocInstance(const TellocConfigPtr configPtr);

void DestroyTellocInstance(TellocInstancePtr* tellocInstancePtr);

void FreeTellocResponse(TellocResponsePtr responsePtr);

/// Generic send command function just for compatibility. In most use cases, its recommended to use the other functions provided.
TellocResponsePtr TellocCommand(TellocInstancePtr tellocInstancePtr, const char* cmd);

#ifdef __cplusplus
}
#endif

#endif
