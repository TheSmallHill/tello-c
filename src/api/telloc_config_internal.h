#ifndef TELLOC_CONFIG_INTERNAL_H
#define TELLOC_CONFIG_INTERNAL_H

#include <string>

struct TellocConfigInternal
{
	TellocConfigInternal();

	virtual ~TellocConfigInternal();

	std::string ip_;
	unsigned int commandPort_;
	unsigned int statePort_;
	unsigned int commandResponseTimeout_ms_;
	unsigned int stateTimeout_ms_;

protected:
	static const char* DEFAULT_IP_;
	static const unsigned int DEFAULT_COMMAND_PORT_;
	static const unsigned int DEFAULT_STATE_PORT_;
	static const unsigned int DEFAULT_COMMAND_RESPONSE_TIMEOUT_MS_;
	static const unsigned int DEFAULT_STATE_TIMEOUT_MS_;
};

#endif
