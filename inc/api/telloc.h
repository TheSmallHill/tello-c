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

void FreeTellocResponse(TellocResponseTypePtr responsePtr);

#ifdef __cplusplus
}
#endif

#endif
