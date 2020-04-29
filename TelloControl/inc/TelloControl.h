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
   
   Response DoTakeoff();
   
   Response DoLand();
   
protected:
   Response GetResponse();

   /// @name Services
   /// @{
   boost::asio::io_service service_;
   /// #}
   
   /// @name Sockets
   /// @{
   boost::asio::ip::udp::socket senderSocket_;
   boost::asio::ip::udp::socket receiverSocket_;
   /// @}
   
   /// @name Endpoints
   /// @{
   boost::asio::ip::udp::endpoint remoteEndpoint_;
   boost::asio::ip::udp::endpoint localEndpoint_;
   /// @}
   
   /// @name Static Variables
   /// @{
   static const unsigned int SENDER_PORT = 8889;
   static const std::string REMOTE_ADDRESS;
   static const std::string LOCAL_ADDRESS;
   /// @}
};

#endif
