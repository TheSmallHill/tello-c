#ifndef TELLOC_INSTANCE_INTERNAL_H
#define TELLOC_INSTANCE_INTERNAL_H

#include "api/telloc_config_internal.h"

#include <memory>

namespace udp
{
class Client;
}

struct TellocResponse;

struct TellocInstanceInternal
{
	TellocInstanceInternal(const TellocConfigInternal& config);

	virtual ~TellocInstanceInternal();

	TellocResponse* ExecuteCommand(const std::string& cmd);

protected:
	enum class ReturnType
		: int
	{
		OK = 0,
		OK_FLOAT_VALUE = 1,
		TELLO_ERROR = 2,
		TELLOC_ERROR = 3
	};

	const TellocConfigInternal config_;

	std::unique_ptr<udp::Client> udpClient_;
};

#endif
