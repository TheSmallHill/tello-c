#ifndef TELLO_TYPES_H
#define TELLO_TYPES_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TellocResponse
{
	int type;

	// Float return
	float fval;

	// String return (for errors)
	char* str;
	size_t len;
} TellocResponseType;

typedef TellocResponseType* TellocResponseTypePtr;

typedef struct TelloState
{
	int missionPad;

	int x_cm;
	int y_cm;
	int z_cm;

	float pitch_rad;
	float roll_rad;
	float yaw_rad;

	int vgx_cmps;
	int vgy_cmps;
	int vgz_cmps;

	int templ_c;
	int temph_c;

	unsigned int timeOfFlightDistance_cm;

	unsigned int height_cm;

	unsigned int batteryPercent;

	float baro_cm;

	unsigned int motorTime_sec;

	float agx_cmps2;
	float agy_cmps2;
	float agz_cmps2;
} TelloStateType;

#ifdef __cplusplus
}
#endif

#endif
