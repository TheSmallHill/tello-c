#include <vector>
#include <iostream>

#include <boost/array.hpp>

#include "TelloControl.h"

const std::string TelloControl::REMOTE_ADDRESS = "192.168.10.1";
const std::string TelloControl::LOCAL_ADDRESS = "0.0.0.0";

TelloControl::TelloControl()
   : service_()
   , senderSocket_(service_)
   , receiverSocket_(service_)
   , remoteEndpoint_(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(REMOTE_ADDRESS), SENDER_PORT))
      , localEndpoint_(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(LOCAL_ADDRESS), SENDER_PORT))
{
   // Open the local sockets
   senderSocket_.open(boost::asio::ip::udp::v4());
   receiverSocket_.open(boost::asio::ip::udp::v4());
}

TelloControl::~TelloControl()
{
   senderSocket_.close();
   receiverSocket_.close();
}

TelloControl::Response TelloControl::ToggleCommandMode()
{
   boost::system::error_code error;
   std::size_t sent = senderSocket_.send_to(boost::asio::buffer("command"), remoteEndpoint_, 0, error);
   
   return GetResponse();
   //return Response::OK;
}

TelloControl::Response TelloControl::DoTakeoff()
{
      boost::system::error_code error;
   std::size_t sent = senderSocket_.send_to(boost::asio::buffer("takeoff"), remoteEndpoint_, 0, error);
   
   /// @todo listen for a return status code and use that to change actual return
   
   return Response::OK;
}

TelloControl::Response TelloControl::DoLand()
{
      boost::system::error_code error;
   std::size_t sent = senderSocket_.send_to(boost::asio::buffer("land"), remoteEndpoint_, 0, error);
   
   /// @todo listen for a return status code and use that to change actual return
   
   return Response::OK;
}

TelloControl::Response TelloControl::GetResponse()
{
   /// @todo need to figure out the asio receive
   
   return Response::OK;
}
