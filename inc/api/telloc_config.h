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

void SetCommandPort(TellocConfigPtr configPtr, const unsigned int port);

void SetStatePort(TellocConfigPtr configPtr, const unsigned int port);

/// @}

/// @name Getters
/// @{

const char* GetIpAddress(const TellocConfigPtr configPtr);

unsigned int GetCommandPort(const TellocConfigPtr configPtr);

unsigned int GetStatePort(const TellocConfigPtr configPtr);

/// @}

#ifdef __cplusplus
}
#endif

#endif
