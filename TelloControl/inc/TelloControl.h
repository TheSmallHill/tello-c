#ifndef TELLO_CONTROL_H
#define TELLO_CONTROL_H

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
   
protected:
   Response EnterCommandMode();
   
   /// @name Services
   /// @{
   boost::asio::io_service senderService_;
   /// #}
   
   /// @name Sockets
   /// @{
   boost::asio::ip::udp::socket senderSocket_;
   /// @}
   
   /// @name Endpoints
   /// @{
   boost::asio::ip::udp::endpoint remoteEndpoint_;
   /// @}
   
   /// @name Static Variables
   /// @{
   static const unsigned int SENDER_PORT = 8889;
   static const std::string REMOTE_ADDRESS = "192.168.10.1";
   /// @}
};

#endif
