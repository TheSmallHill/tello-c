#include <vector>
#include <iostream>

#include <boost/array.hpp>

#include "TelloControl.h"

const std::string TelloControl::REMOTE_ADDRESS = "192.168.10.1";

TelloControl::TelloControl()
   : service_()
   , socket_(service_)
   , remoteEndpoint_(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(REMOTE_ADDRESS), SENDER_PORT))
{
   // Open the local sockets
   socket_.open(boost::asio::ip::udp::v4());
}

TelloControl::~TelloControl()
{
   socket_.close();
}

TelloControl::Response TelloControl::ToggleCommandMode()
{    
   return SendCommand("command");

}

TelloControl::Response TelloControl::Takeoff()
{    
   return SendCommand("takeoff");

}

TelloControl::Response TelloControl::Land()
{    
   return SendCommand("land");

}

TelloControl::Response TelloControl::FlyForward(int x_cm)
{
   return SendCommand("forward " + std::to_string(x_cm));
}

TelloControl::Response TelloControl::SendCommand(const std::string& cmd)
{
   socket_.send_to(boost::asio::buffer(cmd), remoteEndpoint_);
   boost::array<char, 5> recvBuffer;
   std::size_t len = socket_.receive(boost::asio::buffer(recvBuffer));
   
   std::string resp("");
   std::copy(recvBuffer.begin(), recvBuffer.begin() + len, std::back_inserter(resp));
   
   std::cout << resp << std::endl;
   
   return resp == "ok" ? Response::OK : Response::ERROR;
}
