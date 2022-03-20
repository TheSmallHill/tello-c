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

protected:
	static const char* DEFAULT_IP_;
	static const unsigned int DEFAULT_COMMAND_PORT_;
	static const unsigned int DEFAULT_STATE_PORT_;
};

#endif
