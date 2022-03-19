#ifndef TELLOC_CONFIG_H
#define TELLOC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

struct TellocConfigInternal;

typedef struct TellocConfigInternal* TellocConfigPtr;

TellocConfigPtr CreateTellocConfigInstance();

void DestroyTellocConfigInstance(TellocConfigPtr* configPtr);

/// @name Setters
/// @{

void SetIpAddress(TellocConfigPtr configPtr, const char* ip);

void SetPort(TellocConfigPtr configPtr, const unsigned int port);

/// @}

/// @name Getters
/// @{

const char* GetIpAddress(const TellocConfigPtr configPtr);

unsigned int GetPort(const TellocConfigPtr configPtr);

/// @}

#ifdef __cplusplus
}
#endif

#endif
