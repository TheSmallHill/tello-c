#include <boost/asio.hpp>

#include "TelloControl.h"

TelloControl::TelloControl()
   : senderService_()
   , senderSocket_(senderService_)
   , remoteEndpoint_(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(REMOTE_ADDRESS)))
{
   // Open the local socket
   senderSocket.open(boost::asio::ip::udp::v4());
}

TelloControl::Response TelloControl::EnterCommandMode()
{
   // return error since function is currently unimplemented
   return Response::ERROR;
}
