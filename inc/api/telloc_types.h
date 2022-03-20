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

	float x_cm;
	float y_cm;
	float z_cm;

	float pitch_rad;
	float roll_rad;
	float yaw_rad;

	float vgx_cmps;
	float vgy_cmps;
	float vgz_cmps;

	float templ_c;
	float temph_c;

	float timeOfFlightDistance_cm;

	float height_cm;

	float batteryPercent;

	float baro_cm;

	float motorTime_sec;

	float agx_cmps2;
	float agy_cmps2;
	float agz_cmps2;
} TelloStateType;

#ifdef __cplusplus
}
#endif

#endif
