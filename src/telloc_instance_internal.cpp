#include "api/telloc_types.h"

#include "telloc_instance_internal.h"

#include "udp/client.h"
#include "udp/server.h"

#include <cstring>
#include <iostream>

const char* TellocInstanceInternal::OK_RESPONSE_STRING_ = "OK";
const char* TellocInstanceInternal::ERROR_RESPONSE_STRING_ = "ERROR";
const float TellocInstanceInternal::DEG_TO_RAD_ = 0.01745;

TellocInstanceInternal::TellocInstanceInternal(const TellocConfigInternal& config)
	: config_(config)
	, udpCommandClientPtr_(new udp::Client(config.ip_, config.commandPort_))
	, udpCommandResponseServerPtr_(new udp::Server(config.ip_, config.commandPort_))
	, udpStateServerPtr_(new udp::Server(config.ip_, config.statePort_))
	, stopStateListener_(false)
	, stateUpdateThreadPtr_(nullptr)
{
	// Start the thread that monitors state
	if (udpStateServerPtr_)
	{

	}
}

TellocInstanceInternal::~TellocInstanceInternal()
{
	stopStateListener_.store(true);
}

TellocResponse* TellocInstanceInternal::ExecuteCommand(const std::string& cmd)
{
	TellocResponse* replyPtr = nullptr;

	// Need a non empty command in order to do anything
	if (!cmd.empty())
	{
		// Send the command to the Tello, save return just in case we get a bad response from Tello or we just timeout
		const int socketReturn = udpCommandClientPtr_->Send(cmd);

		// Immediately start waiting for a response
		std::string responseMsg;
		const bool rcvStatus = udpCommandResponseServerPtr_->ReceiveNonBlocking(config_.commandResponseTimeout_ms_, responseMsg);

		if (rcvStatus)
		{
			// There is enough to return so figure it out and setup the reply message
			replyPtr = new TellocResponse();

			// Actually got a response so handle it
			if (responseMsg.find(OK_RESPONSE_STRING_) != std::string::npos)
			{
				const std::list<std::string> iterableResponse = SeparateStatusFromResponse(responseMsg);
				if (iterableResponse.size() == 1)
				{
					// Only one element means its just an ack
					replyPtr->type = static_cast<int>(ResponseType::OK);
				}
				else if (iterableResponse.size() == 2)
				{
					// 2 elements means its an ack and a value (like from the basic get commands)
					replyPtr->type = static_cast<int>(ResponseType::OK_FLOAT_VALUE);
					replyPtr->fval = std::stof(iterableResponse.back());
				}
				else
				{
					replyPtr->type = static_cast<int>(ResponseType::TELLO_ERROR);
					const char* str = "Unrecognized response from Tello";

					const std::size_t stringLength = strlen(str);
					replyPtr->str = new char[stringLength];
					std::strcpy(replyPtr->str, str);
					replyPtr->len = stringLength;
				}
			}
			else if (responseMsg.find(ERROR_RESPONSE_STRING_) != std::string::npos)
			{
				const std::list<std::string> iterableResponse = SeparateStatusFromResponse(responseMsg);
				if (iterableResponse.size() == 1)
				{
					replyPtr->type = static_cast<int>(ResponseType::TELLO_ERROR);
				}
				else
				{ // Tello SDK says nothing about what error return codes could be so just treat them as unrecognized
					replyPtr->type = static_cast<int>(ResponseType::TELLO_ERROR);
					const char* str = "Unrecognized error response from Tello";

					const std::size_t stringLength = strlen(str);
					replyPtr->str = new char[stringLength];
					std::strcpy(replyPtr->str, str);
					replyPtr->len = stringLength;
				}
			}
			else
			{
				// Too complex for this interface, assuming that client requested something with a complex response, so just return
				// the response "in the raw".
				replyPtr->type = static_cast<int>(ResponseType::OK_STRING_VALUE);

				replyPtr->str = new char[responseMsg.length()];
				std::strcpy(replyPtr->str, responseMsg.c_str());
				replyPtr->len = responseMsg.length();
			}
		}
		else
		{
			// Unable to receive anything before timeout, use socket return from send to come up with a return
			replyPtr = new TellocResponse();
			replyPtr->type = static_cast<int>(ResponseType::TELLOC_ERROR);
			replyPtr->str = CreateSocketErrorMessage();
			replyPtr->len = strlen(replyPtr->str);
		}
	}

	return replyPtr;
}

TelloStateType TellocInstanceInternal::GetCurrentState() const
{
	std::lock_guard<std::mutex> lg(stateMtx_);
	return currentState_;
}

char* TellocInstanceInternal::CreateSocketErrorMessage()
{
	char* errorMessage = nullptr;
	switch(errno)
	{
	case EACCES:
	{
		const char* msg = "Write permission denied on destination socket file, or search permission is denied for one of the directories the path prefix.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EAGAIN /* | EWOULDBLOCK */:
	{
		const char* msg = "Write permission is denied on the destination socket file, or search permission is denied for one of the directories the path prefix.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EBADF:
	{
		const char* msg = "An invalid descriptor was specified.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ECONNRESET:
	{
		const char* msg = "Connection reset by peer.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EDESTADDRREQ:
	{
		const char* msg = "The socket is not connection-mode, and no peer address is set.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EFAULT:
	{
		const char* msg = "An invalid user space address was specified for an argument.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EINTR:
	{
		const char* msg = "A signal occurred before any data was transmitted.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EINVAL:
	{
		const char* msg = "Invalid argument passed.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EISCONN:
	{
		const char* msg = "The connection-mode socket was connected already but a recipient was specified.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EMSGSIZE:
	{
		const char* msg = "The socket type requires that message be sent atomically, and the size of the message to be sent made this impossible.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOBUFS:
	{
		const char* msg = "The output queue for a network interface is full.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOMEM:
	{
		const char* msg = "No memory available";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOTCONN:
	{
		const char* msg = "The socket is not connected, and no target has been given.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case ENOTSOCK:
	{
		const char* msg = "The argument for sockfd is not a socket";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EOPNOTSUPP:
	{
		const char* msg = "Some bit in the flags argument is inappropriate for the socket type";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	case EPIPE:
	{
		const char* msg = "The local end has been shut down on a connection oriented socket.";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	default:
	{
		const char* msg = "Unknown socket error detected!";
		errorMessage = reinterpret_cast<char*>(malloc(strlen(msg) + 1));
		break;
	}
	}

	return errorMessage;
}

std::list<std::string> TellocInstanceInternal::SeparateStatusFromResponse(const std::string& msg) const
{
	std::list<std::string> separatedReturnStrings;

	char* msgCpyOriginal = new char[msg.length()];
	char* mspCpyMvg = std::strcpy(msgCpyOriginal, msg.c_str());

	char* token = std::strtok(mspCpyMvg, " ");
	while(token != NULL)
	{
		separatedReturnStrings.push_back(std::string(token, strlen(token)));
		token = std::strtok(NULL, " ");
	}

	delete msgCpyOriginal;
	msgCpyOriginal = nullptr;

	return separatedReturnStrings;
}

void TellocInstanceInternal::StateHandlerFcn()
{
	while (!stopStateListener_.load())
	{
		// Get mutex lock
		udpStateServerMtx_.lock();

		std::string msg;
		if (!udpStateServerPtr_->ReceiveNonBlocking(config_.stateTimeout_ms_, msg))
		{
			// Something bad is going on with the state, shut down the thread and throw an exception
			stopStateListener_.store(true);
			/// @todo throw an exception
		}

		TelloStateType newState = GetState(msg);
		UpdateState(newState);
	}
}

TelloStateType TellocInstanceInternal::GetState(const std::string& msg) const
{
	TelloStateType newState;

	std::vector<std::string> separatedState;

	SeparateStringByDelimiter(msg, ";", separatedState);

	for (std::size_t i = 0; i < separatedState.size(); i++)
	{
		const std::string& str = separatedState[i];
		std::vector<std::string> keyValue;

		SeparateStringByDelimiter(str, ":", keyValue);

		const std::string& key = keyValue.front();
		const std::string& value = keyValue.back();

		if (key.compare("pitch"))
		{
			newState.pitch_rad = std::stof(value) * DEG_TO_RAD_;
		}
		else if (key.compare("roll"))
		{
			newState.roll_rad = std::stof(value) * DEG_TO_RAD_;
		}
		else if (key.compare("yaw"))
		{
			newState.yaw_rad = std::stof(value) * DEG_TO_RAD_;
		}
		else if (key.compare("vgx"))
		{
			newState.vgx_cmps = std::stoi(value);
		}
		else if (key.compare("vgy"))
		{
			newState.vgy_cmps = std::stoi(value);
		}
		else if (key.compare("vgz"))
		{
			newState.vgz_cmps = std::stoi(value);
		}
		else if (key.compare("templ"))
		{
			newState.templ_c = std::stoi(value);
		}
		else if (key.compare("temph"))
		{
			newState.temph_c = std::stoi(value);
		}
		else if (key.compare("tof"))
		{
			newState.timeOfFlightDistance_cm = static_cast<unsigned int>(std::stoi(value));
		}
		else if (key.compare("h"))
		{
			newState.height_cm = static_cast<unsigned int>(std::stoi(value));
		}
		else if (key.compare("bat"))
		{
			newState.batteryPercent = static_cast<unsigned int>(std::stoi(value));
		}
		else if (key.compare("baro"))
		{
			newState.baro_cm = std::stof(value);
		}
		else if (key.compare("time"))
		{
			newState.motorTime_sec = static_cast<unsigned int>(std::stoi(value));
		}
		else if (key.compare("agx"))
		{
			newState.agx_cmps2 = std::stof(value);
		}
		else if (key.compare("agy"))
		{
			newState.agy_cmps2 = std::stof(value);
		}
		else if (key.compare("agz"))
		{
			newState.agz_cmps2 = std::stof(value);
		}
		else
		{
			std::cerr << "Unrecognized parameter in Tello state!" << std::endl;
		}
	}

	return newState;
}

void TellocInstanceInternal::UpdateState(const TelloStateType& newState)
{
	std::lock_guard<std::mutex> lg(stateMtx_);

	currentState_ = newState;
}

void TellocInstanceInternal::SeparateStringByDelimiter(const std::string& str, const std::string& del, std::vector<std::string>& separated) const
{
	std::string strCpy(str);

	// Get a more separated representation of the state message since it was delimited
	std::size_t pos = 0;
	std::string token;
	while ((pos = strCpy.find(del)) != std::string::npos)
	{
		token = strCpy.substr(0, pos);
		separated.push_back(token);
		strCpy.erase(0, pos + del.size());
	}
}
