#ifndef TELLO_CONTROL_H
#define TELLO_CONTROL_H

#include <boost/asio.hpp>

#include <string>

class TelloControl
{
public:
   /// Enumeration of possible command responses.
   enum Response
   {
      OK,
      ERROR
   };
   
   /// Constructor for the TelloControl object that connects to the correct network and puts into SDK mode.
   TelloControl();
   
   ~TelloControl();
   
   Response ToggleCommandMode();
   
   Response Takeoff();
   
   Response Land();
   
   Response FlyForward(int x_cm);
   
protected:
   Response SendCommand(const std::string& cmd);

   /// @name Services
   /// @{
   boost::asio::io_service service_;
   /// #}
   
   /// @name Sockets
   /// @{
   boost::asio::ip::udp::socket socket_;
   /// @}
   
   /// @name Endpoints
   /// @{
   boost::asio::ip::udp::endpoint remoteEndpoint_;
   /// @}
   
   /// @name Static Variables
   /// @{
   static const unsigned int SENDER_PORT = 8889;
   static const std::string REMOTE_ADDRESS;
   /// @}
};

#endif
