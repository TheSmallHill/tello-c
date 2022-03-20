#ifndef TELLO_TYPES_H
#define TELLO_TYPES_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct TellocResponse
{
	int type;

	// Float return
	float fval;

	// String return (for errors)
	char* str;
	size_t len;
};

typedef struct TellocResponse* TellocResponsePtr;

#ifdef __cplusplus
}
#endif

#endif
