#ifndef TELLO_TYPES_H
#define TELLO_TYPES_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OK = 0x00;
#define OK_FLOAT_VALUE = 0x01;
#define ERROR = 0x02;

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
