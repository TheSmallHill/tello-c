#include <iostream>

#include "TelloControl.h"

const std::string TelloControl::REMOTE_ADDRESS = "192.168.10.1";

TelloControl::TelloControl()
   : senderService_()
   , senderSocket_(senderService_)
   , remoteEndpoint_(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(REMOTE_ADDRESS), SENDER_PORT))
{
   // Open the local socket
   senderSocket_.open(boost::asio::ip::udp::v4());
}

TelloControl::~TelloControl()
{
   senderSocket_.close();
}

TelloControl::Response TelloControl::EnterCommandMode()
{
   boost::system::error_code error;
   auto sent = senderSocket_.send_to(boost::asio::buffer("Command"), remoteEndpoint_, 0, error);
   
   std::cout << sent << std::endl;
   
   return Response::ERROR;
}
