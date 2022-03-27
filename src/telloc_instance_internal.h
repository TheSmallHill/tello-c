#ifndef TELLOC_INSTANCE_INTERNAL_H
#define TELLOC_INSTANCE_INTERNAL_H

#include "api/telloc_config_internal.h"

#include <memory>

#include <list>
#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <atomic>


namespace udp
{
class Client;
class Server;
}

struct TellocResponse;

struct TellocInstanceInternal
{
	TellocInstanceInternal(const TellocConfigInternal& config);

	virtual ~TellocInstanceInternal();

	TellocResponse* ExecuteCommand(const std::string& cmd);

	TelloStateType GetCurrentState() const;

protected:
	enum class ResponseType
		: int
	{
		OK = 0,
		OK_FLOAT_VALUE = 1,
		OK_STRING_VALUE = 2,
		TELLO_ERROR = 3,
		TELLOC_ERROR = 4
	};

	char* CreateSocketErrorMessage();

	std::list<std::string> SeparateStatusFromResponse(const std::string& msg) const;

	void StateHandlerFcn();

	TelloStateType GetState(const std::string& msg) const;

	void UpdateState(const TelloStateType& newState);

	void SeparateStringByDelimiter(const std::string& str, const std::string& del, std::vector<std::string>& separated) const;

	const TellocConfigInternal config_;

	std::unique_ptr<udp::Client> udpCommandClientPtr_;
	std::unique_ptr<udp::Server> udpCommandResponseServerPtr_;

	std::unique_ptr<udp::Server> udpStateServerPtr_;
	std::mutex udpStateServerMtx_;
	std::atomic<bool> stopStateListener_;

	std::unique_ptr<std::thread> stateUpdateThreadPtr_;

	TelloStateType currentState_;
	mutable std::mutex stateMtx_;

	static const char* OK_RESPONSE_STRING_;
	static const char* ERROR_RESPONSE_STRING_;
	static const float DEG_TO_RAD_;
};

#endif
