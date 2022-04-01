#ifndef TELLOC_INSTANCE_INTERNAL_H
#define TELLOC_INSTANCE_INTERNAL_H

#include "api/telloc_config_internal.h"

#include <memory>

#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <atomic>

/// @name Forward Declarations
/// @{
namespace udp
{
class Client;
class Server;
}

struct TellocResponse;
/// @}

/// Internal instance of the tello-c that contains all actual functionality that we expose via the C API.
struct TellocInstanceInternal
{
	/// Constructor using the configuration structure.
	/// @param[in] config Configuration structure containing all parameters needed to connect to a Tello and initialize the
	/// library.
	TellocInstanceInternal(const TellocConfigInternal& config);

	/// Destructor
	virtual ~TellocInstanceInternal();

	/// Gets the current state of the Tello.
	/// @return Structure containing state data for the Tello.
	TelloStateType GetCurrentState() const;

	bool GetVideoStreamStatus() const;

	/// @name Core Movement Commands
	/// @{
	TellocResponse* CommandTakeoff();

	TellocResponse* CommandLand();

	TellocResponse* CommandEnableVideoStream();

	TellocResponse* CommandDisableVideoStream();

	TellocResponse* CommandEmergency();

	TellocResponse* CommandUp(const unsigned int up_cm);

	TellocResponse* CommandDown(const unsigned int down_cm);

	TellocResponse* CommandLeft(const unsigned int left_cm);

	TellocResponse* CommandRight(const unsigned int right_cm);

	TellocResponse* CommandForward(const unsigned int forward_cm);

	TellocResponse* CommandBackward(const unsigned int backward_cm);

	TellocResponse* CommandRotateCW(const unsigned int cw_rad);

	TellocResponse* CommandRotateCCW(const unsigned int ccw_rad);
	/// @}

protected:
	/// Enumeration used to denote the type of the response we received from Tello.
	enum class ResponseType
		: int
	{
		OK = 0,
		OK_FLOAT_VALUE = 1,
		OK_STRING_VALUE = 2,
		TELLO_ERROR = 3,
		TELLOC_ERROR = 4
	};

	/// Generically executes a command that is passed in via a string.
	/// @param[in] cmd String containing the command to execute.
	/// @return The response from the Tello drone.
	/// @retval nullptr The passed command string was empty.
	/// @note This function is protected since it contains no further management of the Tello state and has no way to validate the
	/// commands given to it. Validation must be done using the command specific function.
	TellocResponse* ExecuteCommand(const std::string& cmd);

	/// Gets the error message for the current socket error.
	/// @return C string containing the socket error message.
	/// @note Upon creating the message, it is the responsibility of the client to manage the memory. However, the
	/// FreeTelloResponse API function will perform this cleanup assuming it is called. An error message is never returned on its
	/// own.
	char* CreateSocketErrorMessage();

	/// Worker function used by the state update thread.
	void StateHandlerFcn();

	/// Extracts the Tello state from the given message.
	/// @param[in] msg Message containing the Tello state.
	/// @return Structure containing the Tello state.
	/// @note Only handles the case where mission pad detection is disabled.
	TelloStateType GetState(const std::string& msg) const;

	/// Updates the internal state (the one stored within the class) using the passed structure.
	/// @param[in] newState The state that the internal state will be updated with.
	void UpdateState(const TelloStateType& newState);

	/// Convenience function to break up a string by a delimiter.
	/// @param[in] str The string that is being separated.
	/// @param[in] del The delimiter to use for separation.
	/// @param[out] separated The string in separated form.
	void SeparateStringByDelimiter(const std::string& str, const std::string& del, std::vector<std::string>& separated) const;

	const TellocConfigInternal config_; ///< The values that were used to configure the interface.

	/// @name UDP Clients/Servers
	/// @{
	std::unique_ptr<udp::Client> udpCommandClientPtr_;
	std::unique_ptr<udp::Server> udpCommandResponseServerPtr_;
	std::unique_ptr<udp::Server> udpStateServerPtr_;
	/// @}

	/// @name Thread Control Variables
	/// @{
	std::mutex udpStateServerMtx_;
	std::atomic<bool> stopStateListener_;
	mutable std::mutex stateMtx_;
	/// @}

	/// Pointer to the thread that is keeping the state up to date. Unique pointer allows for easier management of its memory.
	std::unique_ptr<std::thread> stateUpdateThreadPtr_;

	TelloStateType currentState_; ///< The current state of the Tello.

	bool isVideoStreamEnabled_;

	/// @name Response Constants
	/// @{
	static const char* OK_RESPONSE_STRING_;
	static const char* ERROR_RESPONSE_STRING_;
	/// @}

	/// @name Unit Constants
	/// @{
	static const float DEG_TO_RAD_;
	static const float RAD_TO_DEG_;
	/// @}
};

#endif
